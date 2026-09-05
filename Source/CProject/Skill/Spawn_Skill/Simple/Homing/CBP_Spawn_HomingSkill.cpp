// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Spawn_Skill/Simple/Homing/CBP_Spawn_HomingSkill.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"

#include "Character/CBP_Character.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Macro/MyMacro.h"
#include "Macro/MathMacro.h"
#include "Macro/KismetMacro.h"


#include "Logger/Logger.h"

ACBP_Spawn_HomingSkill::ACBP_Spawn_HomingSkill()
{
//	SetMesh(EMeshType::StaticMesh);
}

void ACBP_Spawn_HomingSkill::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);
}

void ACBP_Spawn_HomingSkill::BeginPlay()
{
	Super::BeginPlay();

	attackComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentBeginOverlap);
}

void ACBP_Spawn_HomingSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isHoming == false) return;

	if (TargetCompleted == false)
	{
		float Y_Value; // À§¾Æ·¡
		float Z_Value; // ÁÂ¿ì

		FVector targetLocation = GetHommingTargetLocation();
		FVector forwardVector = GetActorForwardVector();

		FVector targetVector = targetLocation - GetActorLocation();
		targetVector.Normalize();
		
		Y_Value = (forwardVector.Z > targetVector.Z) ? -1 : 1;
		Y_Value = (abs(forwardVector.Z - targetVector.Z) < 0.01f) ? 0 : Y_Value;

		if (UKismetMathLibrary::DegAcos(FVector::DotProduct(forwardVector, targetVector)) < 1)
		{
			Z_Value = 0;
		}
		else
		{
			Z_Value = (FVector::CrossProduct(forwardVector, targetVector).Z > 0) ? 1 : -1;
		}

		if (Z_Value == 0 && Y_Value == 0)
		{
			TargetCompleted = true;
		}
		else
		{
			FRotator addRotator;
			addRotator.Yaw = Z_Value * DeltaTime * rotationValue;
			addRotator.Pitch = Y_Value * DeltaTime * rotationValue;

			SetActorRotation(GetActorRotation() + addRotator);
		}
	}

	FVector newLocation = GetActorLocation() + GetActorForwardVector() * DeltaTime * moveSpeed;
	SetActorLocation(newLocation);

}

void ACBP_Spawn_HomingSkill::Play(bool const InSuccess, bool & Success)
{
	Super::Play(InSuccess, Success);

	KismetDelay(TEXT("StartHoming"), this, delayTime);

//	actionInfo.ExecutionFunction = TEXT("SetTargetHoming");
//	UKismetSystemLibrary::Delay(this, SetTargetTime, actionInfo);
}

void ACBP_Spawn_HomingSkill::StartHoming()
{
	SetStart();
	isHoming = true;

	float time = (SetTargetTime - delayTime < 0) ? 0 : SetTargetTime - delayTime;

	KismetDelay(TEXT("SetTargetHoming"), this, time);
}
void ACBP_Spawn_HomingSkill::SetTargetHoming()
{
	if (TargetCompleted == true) return;

	TargetCompleted = true;

	FVector targetLocation = GetHommingTargetLocation();
	FRotator newRotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), targetLocation);
	SetActorRotation(newRotator);

	KismetDelay(TEXT("DestroyThisActor"), this, 10);

}

void ACBP_Spawn_HomingSkill::DestroyThisActor()
{
	SetEnd();
	DestroyActor(this);
}

void ACBP_Spawn_HomingSkill::SetMesh(EMeshType newMeshType)
{
	Super::SetMesh(newMeshType);

	CreateDefaultSubobjectAuto(particle);

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


	switch (meshType)
	{
	case EMeshType::StaticMesh:
		particle->SetupAttachment(staticMesh);
		if(attackComponent != nullptr)
			attackComponent->SetupAttachment(staticMesh);
		break;
	case EMeshType::SkeletalMesh:
		particle->SetupAttachment(skeletalMesh);
		if (attackComponent != nullptr)
			attackComponent->SetupAttachment(skeletalMesh);
		break;
	}

	if (attackComponent != nullptr)
	{
		attackComponent->SetCollisionProfileName(FName("Temp"));
	}
}

void ACBP_Spawn_HomingSkill::SetSpawn(AActor* centerActor)
{
	AActor* result_CenterActor = centerActor;

	if (centerActor == nullptr) result_CenterActor = GetInstigator();

	if (GetInstigator() == nullptr) return;

	worldStartPosition = ActorLocalToWorldLocation(result_CenterActor, centerStartPos);
	SetActorLocation(worldStartPosition);

	startRotation = UKismetMathLibrary::FindLookAtRotation(FVector(0,0,0), localLookVector);
	startRotation += result_CenterActor->GetActorRotation();
	startRotation.Roll += centerStartRotRoll;
	SetActorRotation(startRotation);

	ACBP_Character* character = Cast<ACBP_Character>(GetInstigator());
	if (character == nullptr) return;

	switch (homingType)
	{
	case EHomingSkillType::targetHoming:
		Target = character->target;
		break;
	case EHomingSkillType::characterTemptargetHoming:
		tempTarget = character->targetTemp;
		break;
	case EHomingSkillType::endPosHoming:
		worldEndPosition = ActorLocalToWorldLocation(result_CenterActor, centerEndPos);
		break;
	}

	if (attackComponent != nullptr)
	{
		attackComponent->SetCollisionProfileName(FName("Shot"));
		attackComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

}

void ACBP_Spawn_HomingSkill::SetStart()
{
	particle->BeginTrails(Trail_Start, Trail_End, ETrailWidthMode::ETrailWidthMode_FromCentre, 1.0f);
	attackComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACBP_Spawn_HomingSkill::SetEnd()
{
	particle->EndTrails();
	attackComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


FVector ACBP_Spawn_HomingSkill::GetHommingTargetLocation()
{
	FVector targetLocation;

	switch (homingType)
	{
	case EHomingSkillType::targetHoming:
		if (Target != nullptr)
			targetLocation = Target->GetActorLocation();
		else
			targetLocation = GetInstigator()->GetActorLocation();
		break;
	case EHomingSkillType::characterTemptargetHoming:
		if(tempTarget != nullptr)
			targetLocation = tempTarget->GetComponentLocation();
		else
			targetLocation = GetInstigator()->GetActorLocation();
		break;
	case EHomingSkillType::endPosHoming:
		if (worldEndPosition.Z >= -1000)
			targetLocation = worldEndPosition;
		else
			targetLocation = GetInstigator()->GetActorLocation();
		break;
	case EHomingSkillType::InstigatorHomming:
		targetLocation = GetInstigator()->GetActorLocation();
		break;
	}

	return targetLocation;
}

void ACBP_Spawn_HomingSkill::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ACBP_Character* character = Cast<ACBP_Character>(OtherActor);
	if (character == nullptr)
	{
		if (attackParticle != nullptr)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), attackParticle, GetActorLocation(),
				FRotator(0, 0, 0), FVector(1, 1, 1), true);
		}

		if (attackParticleActorClass != nullptr)
		{
			ACBP_Particle* particleActor;
			FActorSpawnParameters param;

			SpawnActorUseClass(particleActor, attackParticleActorClass, param);
			particleActor->SetActorLocation(GetActorLocation());

			F_ParticleActorData data;
			data.EndDelayTime = 0;
			data.StartDelayTime = 0;

			particleActor->SetParticlesBase({ data });
			particleActor->Play();
		}

		DestroyActor(this);
		return;
	}


	ECharacterDamagedType damageType = ECharacterDamagedType::Failling;
	F_Hp_Update_Value resultDamage;
	character->AddDamage(this, damageType, resultDamage);

	if (damageType == ECharacterDamagedType::Failling) return;


	FTransform transform;
	transform.SetLocation(GetActorLocation());

	if (attackParticle != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), attackParticle, GetActorLocation(),
			FRotator(0, 0, 0), FVector(1, 1, 1), true);
	}

	if (attackParticleActorClass != nullptr)
	{
		ACBP_Particle* particleActor;
		FActorSpawnParameters param;

		SpawnActorUseClass(particleActor, attackParticleActorClass, param);
		particleActor->SetActorLocation(GetActorLocation());

		F_ParticleActorData data;
		data.EndDelayTime = 0;
		data.StartDelayTime = 0;

		particleActor->SetParticlesBase({ data });
		particleActor->Play();
	}

	FVector fontColor = FVector(1, 1, 1);
	float fontSize = 24;

	if (character->characterName == ECharacterName::Player)
		fontSize = 30;

	if (damageType == ECharacterDamagedType::Guard)
	{
		fontColor = FVector(1, 1, 0);
		fontSize *= 0.75f;
	}

	SpawnTextActor(
		FString::FromInt(resultDamage.updateValue * resultDamage.updateCount),
		GetActorLocation(),
		fontColor,
		fontSize);

	DestroyThisActor();
	

}