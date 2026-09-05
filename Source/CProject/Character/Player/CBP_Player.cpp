// Fill out your copyright notice in the Description page of Project Settings.


#include "CBP_Player.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Character/Player/Component/CBP_ParkourComponent.h"

#include "Kismet/KismetMathLibrary.h"

#include "Macro/MyMacro.h"
#include "Macro/IncludeMacro.h"
#include "Macro/MathMacro.h"
#include "Macro/KismetMacro.h"
#include "CBP_PlayerController.h"
#include "Animation/CABP_Player.h"

#include "Logger/Logger.h"

#include MainWeaponPath
#include MeleeMainWeaponPath
#include PairWeaponPath
#include MeleePairWeaponPath
#include NS_InteractionPath


#include "Components/TimelineComponent.h"


ACBP_Player::ACBP_Player()
{

	CreateDefaultSubobjectAuto(SpringArm);
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 500;
	SpringArm->SocketOffset = FVector(0, 0, 80);
	SpringArm->bUsePawnControlRotation = true;

	CreateDefaultSubobjectAuto(Camera);
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;

	InteractionCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentBeginOverlap);
	InteractionCollision->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnComponentEndOverlap);

	CreateDefaultSubobjectAuto(targetSearchCollision);
	targetSearchCollision->SetupAttachment(GetRootComponent());
	targetSearchCollision->SetCollisionProfileName(FName("CharacterSerch"));
	targetSearchCollision->SetSphereRadius(2000);
	targetSearchCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::SerchOnComponentBeginOverlap);
	targetSearchCollision->OnComponentEndOverlap.AddDynamic(this, &ThisClass::SerchOnComponentEndOverlap);

	CreateDefaultSubobjectAuto(ZoomTimeline);
	BlendTimeOnZoomIn = 0.125f;

	CreateDefaultSubobjectAuto(ParkourComponent);
}


void ACBP_Player::BeginPlay()
{
	Super::BeginPlay();

	if (testTarget != nullptr)
	{
		ACBP_Character* testTargetActor;

		FActorSpawnParameters param;

		SpawnActorUseClass(testTargetActor, testTarget, param);

		testTargetActor->SetActorLocation(FVector(2000, 2000, 90));

		target = testTargetActor;
	}

	TargetArmLenght = SpringArm->TargetArmLength;
	SocketOffset = SpringArm->SocketOffset;
	FieldOfView = Camera->FieldOfView;

	if (BlendCurveOnZoomIn != nullptr)
	{
		FOnTimelineFloat OnZoom;
		OnZoom.BindDynamic(this, &ThisClass::Zoom);
		ZoomTimeline->AddInterpFloat(BlendCurveOnZoomIn, OnZoom);
		ZoomTimeline->SetPlayRate(1 / BlendTimeOnZoomIn);
	}


	UpdateInterface(EPlayerInterfaceUpdate::HP_Gauge);
	UpdateInterface(EPlayerInterfaceUpdate::Skill);
	UpdateInterface(EPlayerInterfaceUpdate::Weapon_Inventory);
	UpdateInterface(EPlayerInterfaceUpdate::Item_Inventory);


}

void ACBP_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateInterface(EPlayerInterfaceUpdate::Skill);
	UpdateInterface(EPlayerInterfaceUpdate::Guard_Gauge);
	
}

/* ================================= Interface ==================================================*/

void ACBP_Player::ActionDropping(bool& Success)
{
	Success = false;

	bool canDropping = false;
	CanDropping(canDropping);
	if (canDropping == false) return;

	if (weapon_Inventory.IsValidIndex(cur_Using_Weapon_Num) == false) return;

	ACBP_MainWeapon* mainWeapon = Cast<ACBP_MainWeapon>(weapon_Inventory[cur_Using_Weapon_Num]);
	if (mainWeapon == nullptr) return;

	bool InSuccess = false;
	mainWeapon->DroppingMainWeapon(InSuccess);

	if (InSuccess == false)
	{
		if (ACBP_PlayerController* controller = Cast<ACBP_PlayerController>(GetController()))
		{
			controller->Interface_TextDraw(FName("ActionDropping"), FString("Can't Action Dropping"), FVector2D(0, -200), true, 1, FVector2D(0, -50));
		}
		return;
	}

	main_Weapon = nullptr;
	pair_Weapon = nullptr;

	weapon_Inventory.RemoveAt(cur_Using_Weapon_Num);

	if (interacitonActors.Num() == 0)
		curInteractionSelectNum = 0;
	else
	{
		curInteractionSelectNum = UKismetMathLibrary::Clamp(curInteractionSelectNum, 0, interacitonActors.Num() - 1);
	}

	if (ACBP_PlayerController* controller = Cast<ACBP_PlayerController>(GetController()))
	{
		controller->Interface_InteractionTextUpdate();
	}

	ThisClass::UpdateInterface(EPlayerInterfaceUpdate::Weapon_Inventory);
	Success = true;
}

void ACBP_Player::ActionDodge()
{
	bool canParkour = false;
	CanParkour(canParkour);
	if (canParkour == true)
	{
		ParkourComponent->BeginParkour();

		if (ParkourComponent->ParkourType != EParkourType::None)
		{
			characterState = ECharacterState::Dodge;	// 파쿠르 상태는 dodge상태임

			ClearMontageDelegate();

			GetMesh()->GetAnimInstance()->OnMontageBlendingOut.AddDynamic(ParkourComponent, &UCBP_ParkourComponent::EndParkour);
			MontageDelegate = "ReSetState";

			AddMontageBlendOutDelegate();

			return;
		}
	}

	// 파쿠르 실패했음 여기로옴

	bool canDodge = false;
	CanDodge(canDodge);

	if (!canDodge) return;

	if (character_MontageDataAsset == nullptr) return;

	SetBeforeDodge();

	if (IsValid(GetMesh()->GetAnimInstance()))
	{
		GetMesh()->GetAnimInstance()->Montage_Stop(0.0f);
	}

	characterState = ECharacterState::Dodge;

	F_BaseMontageData montageData;
	character_MontageDataAsset->GetCharacterMontage(ECharacterMontageName::Dodge, montageData);

	PlayMontageCharacter(ThisClass, montageData.Montage, montageData.PlayRate, montageData.Section,
		"ReSetState",
		ThisClass::AddMontageEndedDelegate();
	);

}

void ACBP_Player::Skill(ESkillType InSkillType, bool isPressed)
{
	Super::Skill(InSkillType, isPressed);

	if (isPressed == false) return;

	if (characterState == ECharacterState::Skill) return;
	ACBP_PlayerController* playerController = Cast<ACBP_PlayerController>(GetController());
	if (playerController == nullptr) return;

	playerController->Interface_TextDraw(FName("SkillCoolTimeWidget"),FString("Can't use skill"), FVector2D(0, -200),true, 1, FVector2D(0, -50));

}

/* ================================= Interaction Overlap ========================================*/

void ACBP_Player::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	bool isAdd = false;
	FName widgetName;
	FString widgetString;

	if (auto* object = Cast<ACBP_Interaction_Object>(OtherActor))
	{
		interacitonActors.Add(OtherActor);
		isAdd = true;
		widgetName = FName(object->GetName());
		widgetString = object->widgetName;
	}

	if (auto* object = Cast<ACBP_NS_InteractionObject>(OtherActor))
	{
		interacitonActors.Add(OtherActor);
		isAdd = true;
		widgetName = FName(object->GetName());
		widgetString = object->widgetName;
	}

	if (isAdd == false) return;

	ACBP_PlayerController* playerController = Cast<ACBP_PlayerController>(GetController());
	if (playerController == nullptr) return;

	playerController->Interface_TextBoxDraw(widgetName,FVector(1,1,1), widgetString, FVector2D(300, 0), 1,false,0,FVector2D(0,0));
	playerController->Interface_InteractionTextUpdate();

}

void ACBP_Player::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (interacitonActors.Contains(OtherActor) == true)
	{
		interacitonActors.Remove(OtherActor);

		ACBP_PlayerController* playerController = Cast<ACBP_PlayerController>(GetController());
		if (playerController == nullptr) return;

		playerController->Interface_TextDelete(FName(OtherActor->GetName()));

		if (interacitonActors.Num() == 0)
			curInteractionSelectNum = 0;
		else
		{
			curInteractionSelectNum = UKismetMathLibrary::Clamp(curInteractionSelectNum, 0, interacitonActors.Num() - 1);
		}

		playerController->Interface_InteractionTextUpdate();
	}
}

void ACBP_Player::SerchOnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ACBP_Character* character = Cast<ACBP_Character>(OtherActor);
	if (character == nullptr) return;

	bool hostile = false;
	IsHostile(character->camp, hostile);
	if (hostile == false) return;

	targetCandidate.Add(OtherActor);

	SetUnPauseTimer(CharacterSerchHandle);
}

void ACBP_Player::SerchOnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (targetCandidate.Contains(OtherActor) == true)
	{
		targetCandidate.Remove(OtherActor);
	}
}

/* =====================================================================================*/

void ACBP_Player::SetDodgeDirection()
{
	FVector forwardVector = GetActorForwardVector();

	FVector atForwardVector = (UKismetMathLibrary::GetForwardVector(RotatorXYZ(0, 0, GetControlRotation().Yaw))* dodgeForward);
	FVector atRightVector = (UKismetMathLibrary::GetRightVector(RotatorXYZ(0, 0, GetControlRotation().Yaw)) * dodgeRight);

	FVector LookAtVector = atForwardVector + atRightVector;
	
	UKismetMathLibrary::Vector_Normalize(LookAtVector);

	float AddRotationYaw = 0;
	
	if (!(dodgeForward == 0 && dodgeRight == 0))
	{
		AddRotationYaw = UKismetMathLibrary::DegAcos((FVector::DotProduct(forwardVector, LookAtVector)));
	}

	if (FVector::CrossProduct(forwardVector, LookAtVector).Z <= 0)
		AddRotationYaw *= -1;

	AddActorWorldRotation(RotatorXYZ(0, 0, AddRotationYaw));
}

void ACBP_Player::SetBeforeDodge()
{
	switch (characterState)
	{
	case ECharacterState::Attack:
		AttackSetBeforeDodge();
		break;
	}

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ACBP_Player::StopAIMoveToActor()
{
	GetController()->StopMovement();
}


/* =================================== private =======================================*/
void ACBP_Player::AttackSetBeforeDodge()
{
	if (auto* mainWeapon = Cast<ACBP_MainWeapon>(main_Weapon))
	{
		bool OutSuccess;
		mainWeapon->DeActivate(true, OutSuccess);

		if (auto* weapon = Cast<ACBP_Melee_MainWeapon>(main_Weapon))
			weapon->TrailParticleDeActivate();

	}

	if (auto* pairWeapon = Cast<ACBP_PairWeapon>(pair_Weapon))
	{
		bool OutSuccess;
		pairWeapon->DeActivate(true, OutSuccess);

		if (auto* weapon = Cast<ACBP_Melee_MainWeapon>(main_Weapon))
			weapon->TrailParticleDeActivate();
	}
}

void ACBP_Player::UpdateInterface(EPlayerInterfaceUpdate updateType)
{
	if (updateType == EPlayerInterfaceUpdate::HP_Gauge)
	{
		Cast<ACBP_PlayerController>(GetController())->Player_Hp_Interface();
	}

	if (updateType == EPlayerInterfaceUpdate::Guard_Gauge)
	{
		Cast<ACBP_PlayerController>(GetController())->Player_Guard_Interface();
	}

	if (updateType == EPlayerInterfaceUpdate::Skill)
	{
		Cast<ACBP_PlayerController>(GetController())->Player_Skill_Interface();
	}

	if (updateType == EPlayerInterfaceUpdate::Weapon_Inventory)
	{
		Cast<ACBP_PlayerController>(GetController())->Player_Inventory_Interface();
	}

	if (updateType == EPlayerInterfaceUpdate::Item_Inventory)
	{
		FString itemNameString = FString("");
	
		switch (cur_Using_Item_Num)
		{
		case EItemName::None:
			itemNameString += FString("");
			break;
		case EItemName::HP_Portion:
			itemNameString += FString("HP_S : ");
			break;
		case EItemName::Big_HP_Portion:
			itemNameString += FString("HP_B : ");
			break;
		case EItemName::Max:
			itemNameString += FString("");
			break;
		}

		if (Item_Inventory.Contains(cur_Using_Item_Num) == true)
		{
			itemNameString += FString::FromInt(Item_Inventory[cur_Using_Item_Num]);
		}
		else
		{
			itemNameString += FString::FromInt(0);
		}

		Cast<ACBP_PlayerController>(GetController())->Player_Item_Inventory_Interface(itemNameString);
	}

}

/* =========================== Interaction ================================== */

void ACBP_Player::Interaction()
{
	if (curInteractionSelectNum >= interacitonActors.Num()) return;

	if (characterState != ECharacterState::Idle) return;

	AActor* actor = interacitonActors[curInteractionSelectNum];

	bool Success = false;
	AActor* resultActor = nullptr;

	if (ICBPI_Interaction* interactionActor = Cast<ICBPI_Interaction>(actor))
	{
		interactionActor->Interaction(this, Success, resultActor);
	}

	
	if (Success == false)
	{
		if (ACBP_PlayerController* playerController = Cast<ACBP_PlayerController>(GetController()))
		{
			playerController->Interface_TextDraw(FName("InteractionWidget"), FString("Can't Interaction Object"), FVector2D(0, -200), true, 1, FVector2D(0, -50));
		}
		return;
	}

	bool AddInventorySuccess = false;
	ThisClass::AddInventory(true, resultActor, AddInventorySuccess);

	// Interaction이 꺼지면 자연스럽게 End로 가버림

	if (interacitonActors.Num() == 0)
		curInteractionSelectNum = 0;
	else
	{
		curInteractionSelectNum = UKismetMathLibrary::Clamp(curInteractionSelectNum, 0, interacitonActors.Num() - 1);
	}


	if (ACBP_PlayerController* playerController = Cast<ACBP_PlayerController>(GetController()))
	{
		playerController->Interface_InteractionTextUpdate();
	}
}

void ACBP_Player::InteractionSelect(float Value)
{
	int addNum = Value;

	if (addNum != 0)
	{
		curInteractionSelectNum += addNum;

		if (interacitonActors.Num() == 0)
			curInteractionSelectNum = 0;
		else
		{
			curInteractionSelectNum = UKismetMathLibrary::Clamp(curInteractionSelectNum, 0, interacitonActors.Num() - 1);
		}

		if (ACBP_PlayerController* playerController = Cast<ACBP_PlayerController>(GetController()))
		{
			playerController->Interface_InteractionTextUpdate();
		}

	}

}

void ACBP_Player::SetDie()
{
	Super::SetDie();
}



void ACBP_Player::ZoomCameraIn()
{
	ACBP_MainWeapon* mainWeapon = Cast<ACBP_MainWeapon>(main_Weapon);
	if (mainWeapon == nullptr) return;
	EWeaponName weaponName = mainWeapon->weaponName;

	switch (weaponName)
	{
	case EWeaponName::Rifle:
	case EWeaponName::Bow:
		ZoomTimeline->Play();
		if (UCABP_Player* playerAnim = Cast<UCABP_Player>(GetMesh()->GetAnimInstance()))
		{
			playerAnim->SetZoom(true);
			cur_ZoomMode = true;
		}
		break;
	}
}
void ACBP_Player::ZoomCameraOut()
{
	ZoomTimeline->Reverse();
	if (UCABP_Player* playerAnim = Cast<UCABP_Player>(GetMesh()->GetAnimInstance()))
	{
		playerAnim->SetZoom(false);
		cur_ZoomMode = false;
	}
}

void ACBP_Player::Zoom(float const Alpha)
{
	SpringArm->TargetArmLength = FMath::Lerp(TargetArmLenght, TargetArmLenghtOnZoomIn, Alpha);
	SpringArm->SocketOffset = FMath::Lerp(SocketOffset, SocketOffsetOnZoomIn, Alpha);

	Camera->SetFieldOfView(FMath::Lerp(FieldOfView, FieldOfViewOnZoomIn, Alpha));

}

void ACBP_Player::Parkour()
{
	if (GetCharacterMovement()->IsFalling() == false)
	{
		ParkourComponent->BeginParkour();
	}
}

void ACBP_Player::CanParkour(bool& outCanParkour)
{
	outCanParkour = false;

	switch (characterState)
	{
	case ECharacterState::Idle:
	case ECharacterState::Down:
	case ECharacterState::Dodge:
	case ECharacterState::Jump:
		outCanParkour = true;
		break;
	}
}

void ACBP_Player::Landed(FHitResult const& HitResults)
{
	bool canParkour = false;

	switch (characterState)
	{
	case ECharacterState::Idle:
	case ECharacterState::Jump:
		canParkour = true;
		break;
	}

	if (canParkour == true)
	{
		ParkourComponent->BeginLandedParkour();

		if (ParkourComponent->ParkourType != EParkourType::None)
		{
			characterState = ECharacterState::Dodge;	// 파쿠르 상태는 dodge상태임

			ClearMontageDelegate();

			GetMesh()->GetAnimInstance()->OnMontageBlendingOut.AddDynamic(ParkourComponent, &UCBP_ParkourComponent::EndParkour);
			MontageDelegate = "ReSetState";

			AddMontageBlendOutDelegate();

			return;
		}
	}

	Super::Landed(HitResults);

}

void ACBP_Player::BaseOnMontageBlendingOut()
{
//	GetMesh()->GetAnimInstance()->OnMontageBlendingOut.AddDynamic(ParkourComponent, &UCBP_ParkourComponent::EndParkour);
}

void ACBP_Player::QuestInterfaceUpdate()
{
	ACBP_PlayerController* playerController = Cast<ACBP_PlayerController>(GetController());
	if (playerController == nullptr) return;

	playerController->Interface_QuestUpdate(curQuestActors);
}