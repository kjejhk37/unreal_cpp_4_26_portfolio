// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Non_SimulationObject/CBP_AttackTerrainObject.h"

#include "Components/ShapeComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"

#include "Particle/CBP_Particle.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

#include "UI/CBP_TextActor.h"
#include "Character/Player/CBP_Player.h"

#include "Components/TimelineComponent.h"

#include "Macro/MyMacro.h"
#include "Macro/KismetMacro.h"
#include "Macro/MathMacro.h"

#include "Logger/Logger.h"

ACBP_AttackTerrainObject::ACBP_AttackTerrainObject()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACBP_AttackTerrainObject::Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType)
{
	CreateDefaultSubobjectAuto(center);
	SetRootComponent(center);

	Super::Set_NonSimul_ComponentsBase(newMeshType, newInteractionType);

	attackCollisionType = newInteractionType;

	switch (attackCollisionType)
	{
	case ECollisionType::Box:
		attackComponent = CreateDefaultSubobject<UBoxComponent>("attackComponent");
		break;
	case ECollisionType::Sphere:
		attackComponent = CreateDefaultSubobject<USphereComponent>("attackComponent");
		break;
	case ECollisionType::Capsule:
		attackComponent = CreateDefaultSubobject<UCapsuleComponent>("attackComponent");
		break;
	}

	if (attackCollisionType != ECollisionType::None)
	{
		attackComponent->SetCollisionProfileName(FName("Attack"));
		attackComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	CreateDefaultSubobjectAuto(particleComponent);

	switch (meshType)
	{
	case EMeshType::StaticMesh:
		staticMesh->SetupAttachment(center);
		attackComponent->SetupAttachment(staticMesh);
		particleComponent->SetupAttachment(staticMesh);
		break;
	case EMeshType::SkeletalMesh:
		skeletalMesh->SetupAttachment(center);
		attackComponent->SetupAttachment(skeletalMesh);
		particleComponent->SetupAttachment(skeletalMesh);
		break;
	}

	CreateDefaultSubobjectAuto(AnimationTimeLine);

}

void ACBP_AttackTerrainObject::BeginPlay()
{
	Super::BeginPlay();

	attackComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnAttackComponentBeginOverlap);

	if (BlendCurveOnAnimation != nullptr)
	{
		FOnTimelineFloat OnAnimation;
		OnAnimation.BindDynamic(this, &ThisClass::Animation);
		AnimationTimeLine->AddInterpFloat(BlendCurveOnAnimation, OnAnimation);
		AnimationTimeLine->SetPlayRate(1 / playTime);

//		AnimationTimeLine->Play();
	}

	startLocation = GetActorLocation();
//	startRotator = GetActorRotation();
	startRotator = FRotator(0, 0, 0);

	endRotaotr = startRotator + inEndRotator;
	endLocation = ActorLocalToWorldLocation(this, inEndLocation);

}

void ACBP_AttackTerrainObject::WorkAttackTerrain()
{
	startLocation = GetActorLocation();
	//	startRotator = GetActorRotation();
	startRotator = FRotator(0, 0, 0);

	endRotaotr = startRotator + inEndRotator;
	endLocation = ActorLocalToWorldLocation(this, inEndLocation);

	attackComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AnimationTimeLine->Play();
	KismetDelay(TEXT("StartDelay"), this, 0.25f);
}

void ACBP_AttackTerrainObject::StartDelay()
{
	attackComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	KismetDelay(TEXT("SetClearAttackedActors"), this, attackCoolTime);
}

void ACBP_AttackTerrainObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isNoCollision == true)
	{
		attackComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		isNoCollision = false;
	}

}

void ACBP_AttackTerrainObject::SetClearAttackedActors()
{
	attackedActors.Empty();

	attackComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	isNoCollision = true;

	KismetDelay(TEXT("SetClearAttackedActors"), this, attackCoolTime);
}

void ACBP_AttackTerrainObject::OnAttackComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (attackedActors.Contains(OtherActor) == true)
		return;

	ACBP_Character* otherCharacter = Cast<ACBP_Character>(OtherActor);
	if (otherCharacter == nullptr) return;

	ECharacterDamagedType damageType;
	F_Hp_Update_Value resultDamage;
	otherCharacter->AddDamage(this, damageType, resultDamage);

	if (damageType == ECharacterDamagedType::Failling) return;

	FVector particleLocation = otherCharacter->GetActorLocation();
	
	float temp;
	FVector tempLocation = otherCharacter->GetActorLocation() - GetActorLocation();
	tempLocation.Z = 0;
	tempLocation.ToDirectionAndLength(tempLocation, temp);
	particleLocation += tempLocation * 50;

	SpawnParticle(particleLocation);

	SpawnTextActor(
		FString::FromInt(resultDamage.updateValue * damage.updateCount),
		particleLocation,
		FVector(1, 1, 1),
		24,
		1
	);
}

void ACBP_AttackTerrainObject::SpawnParticle(FVector particleLocation)
{
	if (particle != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particle, particleLocation,
			FRotator(0, 0, 0), FVector(1, 1, 1), true);
	}

	if (particleActorClass != nullptr)
	{
		ACBP_Particle* particleActor;
		FActorSpawnParameters param;

		SpawnActorUseClass(particleActor, particleActorClass, param);
		particleActor->SetActorLocation(particleLocation);

		F_ParticleActorData data;
		data.EndDelayTime = 0;
		data.StartDelayTime = 0;

		particleActor->SetParticlesBase({ data });
		particleActor->Play();
	}
}


void ACBP_AttackTerrainObject::SpawnTextActor(FString string, FVector Location, FVector fontColor, float fontSize, float outlineFontSize)
{
	ACBP_TextActor* textActor;
	FActorSpawnParameters param;

	SpawnActorUseClass(textActor, ACBP_TextActor::StaticClass(), param);
	textActor->SetActorLocation(Location);

	textActor->SetTextFont(fontSize);
	textActor->SetTextOutlineFont(outlineFontSize);
	textActor->SetTextBox(string, fontColor);
}


void ACBP_AttackTerrainObject::Animation(float const Alpha)
{
	FVector newLocation = UKismetMathLibrary::VLerp(startLocation, endLocation, Alpha);

	SetActorLocation(newLocation);

	switch (meshType)
	{
	case EMeshType::StaticMesh:
		staticMesh->SetRelativeRotation(UKismetMathLibrary::RLerp(startRotator, inEndRotator, Alpha, false));
//		staticMesh->SetRelativeLocation(newLocation);
		break;
	case EMeshType::SkeletalMesh:
		skeletalMesh->SetRelativeRotation(UKismetMathLibrary::RLerp(startRotator, inEndRotator, Alpha, false));
//		skeletalMesh->SetRelativeLocation(newLocation);
		break;
	}


	if (Alpha == 1)
	{
		AnimationTimeLine->Reverse();
	}

	if (Alpha == 0)
	{
		AnimationTimeLine->Play();
	}
}


void ACBP_AttackTerrainObject::GetInstigatorcharacter(ACBP_Character*& outCharacter) { outCharacter = nullptr; }
void ACBP_AttackTerrainObject::GetFinalDamage(F_Hp_Update_Value& outDamage) { outDamage = damage; }
void ACBP_AttackTerrainObject::GetAttackType(EAttackType& outAttackType) { outAttackType = attackType; }
void ACBP_AttackTerrainObject::GetAttackHitType(EAttackHitType& outAttackHitType) { outAttackHitType = attackHitType; }
void ACBP_AttackTerrainObject::GetPushVector(FVector& outPushVector) { outPushVector = pushVector; }
void ACBP_AttackTerrainObject::GetAttackPushType(EAttackPushType& outAttackPushType) { outAttackPushType = attackPushType; }
void ACBP_AttackTerrainObject::GetGuardSerchType(EGuardSerchType& outGuardSerchType) { outGuardSerchType = guardSerchType; }