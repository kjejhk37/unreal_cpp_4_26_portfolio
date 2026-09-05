// Fill out your copyright notice in the Description page of Project Settings.


#include "CBP_AICharacter.h"
#include "AIController.h"
#include "Character/AICharacter/Animaion/ACBP_AICharacter.h"

#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/WCBP_ProgressBarBase.h"
#include "Kismet/GameplayStatics.h"

#include "BehaviorTree/BehaviorTree.h"

#include "Macro/MyMacro.h"
#include "Macro/KismetMacro.h"


#include "Interface/CBPI_SpawnerActor.h"

#include "Logger/Logger.h"

ACBP_AICharacter::ACBP_AICharacter()
{
	SetAIPerception();
	CreateDefaultSubobjectAuto(targetSearchCollision);
	targetSearchCollision->SetupAttachment(GetRootComponent());
	targetSearchCollision->SetCollisionProfileName(FName("CharacterSerch"));
	targetSearchCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	targetSearchCollision->SetRelativeLocation(FVector(300, 0, 0));
	targetSearchCollision->SetSphereRadius(1000);

	GetMesh()->SetHiddenInGame(true);

	CreateDefaultSubobjectAuto(Hp_Bar);
	Hp_Bar->SetupAttachment(GetRootComponent());

	auto* const widgetClass = StaticLoadClass(UWCBP_ProgressBarBase::StaticClass(), this, TEXT("WidgetBlueprint'/Game/CBP_Data/UI/WBP_ProgressBar.WBP_ProgressBar_C'"));

	Hp_Bar->SetWidgetSpace(EWidgetSpace::World);
	Hp_Bar->SetWidgetClass(widgetClass);
	Hp_Bar->SetRelativeLocation(FVector(0, 0, 150));

	Hp_Bar->SetUsingAbsoluteRotation(true);

	auto* const GuardwidgetClass = StaticLoadClass(UWCBP_ProgressBarBase::StaticClass(), this, TEXT("WidgetBlueprint'/Game/CBP_Data/UI/WBP_GuardProgressBar.WBP_GuardProgressBar_C'"));

	CreateDefaultSubobjectAuto(Guard_GaugeBar);
	Guard_GaugeBar->SetupAttachment(GetRootComponent());

	Guard_GaugeBar->SetWidgetSpace(EWidgetSpace::World);
	Guard_GaugeBar->SetWidgetClass(GuardwidgetClass);
	Guard_GaugeBar->SetRelativeLocation(FVector(0, 0, 125));

	Guard_GaugeBar->SetUsingAbsoluteRotation(true);
	Guard_GaugeBar->SetVisibility(false);
}


void ACBP_AICharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

}

void ACBP_AICharacter::BeginPlay()
{
	Super::BeginPlay();

	Hp_Bar->SetVisibility(false);

	AICharacterPerseption->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::AI_OnTargetPerceptionUpdate);
//	AICharacterPerseption->OnPerceptionUpdated.AddDynamic(this, &ThisClass::AI_OnPerceptionUpdate);

	F_BaseMontageData BeginMontage;

	if (character_MontageDataAsset != nullptr)
	{
		character_MontageDataAsset->GetCharacterMontage(ECharacterMontageName::Spawn, BeginMontage);
	}

	if(BeginMontage.Montage != nullptr)
	{
		AICharacterPerseption->SetSenseEnabled(UAISense_Sight::StaticClass(), false);
		GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &ThisClass::AICharacterOnMontageEnded);
		GetMesh()->GetAnimInstance()->Montage_Play(BeginMontage.Montage, BeginMontage.PlayRate);
		characterState = ECharacterState::Spawn;
	}
	else
	{
		if (AAIController* controller = Cast<AAIController>(GetController()))
			controller->RunBehaviorTree(AI_BehaviorTree);
		
		if (UACBP_AICharacter* AICharacter = Cast<UACBP_AICharacter>(GetMesh()->GetAnimInstance()))
			AICharacter->SetEndSpawn();
	}

	GetMesh()->SetHiddenInGame(false);

	targetSearchCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::SerchOnComponentBeginOverlap);
	targetSearchCollision->OnComponentEndOverlap.AddDynamic(this, &ThisClass::SerchOnComponentEndOverlap);


	SpawnBaseWeaponCase(WeaponClass);
}


void ACBP_AICharacter::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
	
	APlayerCameraManager* playerManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	if (playerManager == nullptr) return;
	if (Hp_Bar == nullptr) return;

	if (curHp <= 0)
	{
		Hp_Bar->SetVisibility(false);
		Guard_GaugeBar->SetVisibility(false);

		curDeadTime += DeltaTime;
		if (curDeadTime >= DeleteTime)
		{
			DestroyThisCharacter();
		}

		return;
	}

	FVector cameraLocation = playerManager->GetCameraLocation();
	FVector widgetLocation = Hp_Bar->GetComponentLocation();

	FRotator newWidgetRotator = UKismetMathLibrary::FindLookAtRotation(widgetLocation, cameraLocation);
	Hp_Bar->SetWorldRotation(newWidgetRotator);

	if (isGuard == true)
	{
		widgetLocation = Guard_GaugeBar->GetComponentLocation();
		newWidgetRotator = UKismetMathLibrary::FindLookAtRotation(widgetLocation, cameraLocation);
		Guard_GaugeBar->SetWorldRotation(newWidgetRotator);

		if (UWCBP_ProgressBarBase* Guard_progressBar = Cast<UWCBP_ProgressBarBase>(Guard_GaugeBar->GetUserWidgetObject()))
		{
			Guard_progressBar->UpdateProgressBar(GuardGauge, MaxGuardGauge);
		}
	}

	if (SpawnerActor != nullptr && SpawnerWeaponActor != nullptr)
	{
		if (ACBP_Character* character = Cast<ACBP_Character>(SpawnerActor))
		{
			if (character->characterState == ECharacterState::Dead || character->main_Weapon != SpawnerWeaponActor)
			{
				EndSpawn();
			}
		}
	}
}

void ACBP_AICharacter::SetAIPerception()
{
	CreateDefaultSubobjectAuto(AICharacterPerseption);

	UAISenseConfig_Sight* SightConfig = CreateOptionalDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	
	SightConfig->SightRadius = 2000;
	SightConfig->LoseSightRadius = SightConfig->SightRadius + 1000;
	SightConfig->PeripheralVisionAngleDegrees = 45;
	SightConfig->SetMaxAge(1.0f);
	SightConfig->AutoSuccessRangeFromLastSeenLocation = -1;
	SightConfig->PointOfViewBackwardOffset = 100;
	SightConfig->NearClippingRadius = 100;

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	AICharacterPerseption->ConfigureSense(*SightConfig);

}

void ACBP_AICharacter::AI_OnTargetPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus)
{
	TArray<AActor*> curInSightActors;
	AICharacterPerseption->GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), curInSightActors);

	if (targetCandidate.Contains(Actor) == true) return;

	if (curInSightActors.Contains(Actor))
	{
		ACBP_Character* character = Cast<ACBP_Character>(Actor);
		if (character == nullptr) return;

		bool hostile = false;
		IsHostile(character->camp, hostile);
		if (hostile == false) return;

		if (targetCandidate.Contains(Actor) == false)
		{
			targetCandidate.Add(Actor);
			SetUnPauseTimer(CharacterSerchHandle);
		}
	}
	else
	{
		if (targetCandidate.Contains(Actor))
		{
			targetCandidate.Remove(Actor);
		}
	}
}

void ACBP_AICharacter::AI_OnPerceptionUpdate(const TArray<AActor*>& UpdatedActors)
{

}


void ACBP_AICharacter::ActionDropping(bool& Success)
{
	Success = false;

	if (isSpawnAICharacter == true) return;
	int value = rand() % 100;

	if (value >= 50 || camp == ECamp::Player) return;

	if (weapon_Inventory.IsValidIndex(0) == false) return;

	ACBP_MainWeapon* mainWeapon = Cast<ACBP_MainWeapon>(weapon_Inventory[0]);
	if (mainWeapon == nullptr) return;

	bool InSuccess = false;
	mainWeapon->DroppingMainWeapon(InSuccess);

	if (InSuccess == false)
	{
		return;
	}

	main_Weapon = nullptr;
	pair_Weapon = nullptr;
	weaponCase = nullptr;

	weapon_Inventory.Remove(mainWeapon);

	Success = true;
}

void ACBP_AICharacter::SpawnBaseWeapon(TSubclassOf<ACBP_MainWeapon> mainWeaponClass, TSubclassOf<ACBP_PairWeapon> pairWeaponClass)
{
	if (mainWeaponClass != nullptr)
	{

		ACBP_MainWeapon* spawnMainWeapon = nullptr;
		ACBP_PairWeapon* spawnPairWeapon = nullptr;
		FActorSpawnParameters param;

		SpawnActorUseClass(spawnMainWeapon, mainWeaponClass, param);
		ThisClass::main_Weapon = spawnMainWeapon;

		if (pairWeaponClass != nullptr)
		{
			SpawnActorUseClass(spawnPairWeapon, pairWeaponClass, param);
			spawnMainWeapon->pairWeapon = spawnPairWeapon;
			ThisClass::pair_Weapon = spawnPairWeapon;
		}

		bool success;
		spawnMainWeapon->PickUpWeapon(this, success);
		AddInventory(true, spawnMainWeapon, success);

		spawnMainWeapon->SetEquip(this, true);

		if (spawnPairWeapon != nullptr)
			spawnPairWeapon->SetEquip(true);

	}
}

void ACBP_AICharacter::SpawnBaseWeaponCase(TSubclassOf<ACBP_WeaponCase> UsingWeaponClass)
{
	if (UsingWeaponClass == nullptr) return;
	FActorSpawnParameters param;

	SpawnActorUseClass(weaponCase, UsingWeaponClass, param);

	bool success = false;
	AActor* ResultActor = nullptr;
	weaponCase->Interaction(this, success, ResultActor);

	bool AddSuccess = false;
	AddInventory(success, ResultActor, AddSuccess);

	if (AddSuccess == false) return;
	
	main_Weapon = ResultActor;
	ACBP_MainWeapon* castMainWeapon = Cast<ACBP_MainWeapon>(main_Weapon);
	if (castMainWeapon == nullptr) return;

	castMainWeapon->SetEquip(this, true);
	pair_Weapon = castMainWeapon->pairWeapon;

	if (ACBP_PairWeapon* castPairWeapon = Cast<ACBP_PairWeapon>(pair_Weapon))
	{
		castPairWeapon->SetEquip(true);
	}

}

void ACBP_AICharacter::AICharacterOnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	AICharacterPerseption->SetSenseEnabled(UAISense_Sight::StaticClass(), true);
	targetSearchCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	characterState = ECharacterState::Idle;

	if (AAIController* controller = Cast<AAIController>(GetController()))
	{
		controller->RunBehaviorTree(AI_BehaviorTree);
	}

	GetMesh()->GetAnimInstance()->OnMontageEnded.RemoveDynamic(this, &ThisClass::AICharacterOnMontageEnded);
}

void ACBP_AICharacter::UpdateHpWidget()
{
	if (Hp_Bar == nullptr) return;

	UWCBP_ProgressBarBase* progressBar = Cast<UWCBP_ProgressBarBase>(Hp_Bar->GetUserWidgetObject());
	if (progressBar == nullptr) return;

	progressBar->UpdateProgressBar(curHp, maxHp);
	Hp_Bar->SetVisibility(true);

	KismetRetriggerableDelay(TEXT("SetHp_GaugeEnd"), this, 5);
}

void ACBP_AICharacter::SetHp_GaugeEnd()
{
	Hp_Bar->SetVisibility(false);
}

void ACBP_AICharacter::AddDamage(AActor* WeaponActor, ECharacterDamagedType& damageType, F_Hp_Update_Value& resultDamage)
{
	Super::AddDamage(WeaponActor, damageType, resultDamage);

}

void ACBP_AICharacter::SerchOnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ACBP_Character* character = Cast<ACBP_Character>(OtherActor);
	if (character == nullptr) return;

	bool hostile = false;
	IsHostile(character->camp, hostile);
	if (hostile == false) return;

	targetCandidate.Add(OtherActor);

	SetUnPauseTimer(CharacterSerchHandle);
}

void ACBP_AICharacter::SerchOnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void ACBP_AICharacter::SetDie()
{
	Super::SetDie();

	bool InSuccess = false;
	ActionDropping(InSuccess);

	if (ICBPI_SpawnerActor* spawnerActor = Cast<ICBPI_SpawnerActor>(SpawnerActor))
	{
		spawnerActor->SetDeleteSpawnedActor(this);
	}

	curDeadTime = 0;

	KismetDelay(TEXT("DestroyThisCharacter"), this, 5);
}

void ACBP_AICharacter::DestroyThisCharacter()
{
	DestroyActor(weaponCase);
	DestroyActor(this);

}