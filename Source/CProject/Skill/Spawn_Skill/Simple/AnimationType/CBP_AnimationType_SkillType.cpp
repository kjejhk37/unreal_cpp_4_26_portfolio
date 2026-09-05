// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Spawn_Skill/Simple/AnimationType/CBP_AnimationType_SkillType.h"
#include "Components/TimelineComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Character/CBP_Character.h"

#include "Components/ShapeComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"


#include "Macro/KismetMacro.h"
#include "Macro/MyMacro.h"
#include "Macro/MathMacro.h"

#include "Logger/Logger.h"

ACBP_AnimationType_SkillType::ACBP_AnimationType_SkillType()
{

}

void ACBP_AnimationType_SkillType::OnConstruction(const FTransform& Transform) 
{
	Super::OnConstruction(Transform);

}

void ACBP_AnimationType_SkillType::BeginPlay()
{
	Super::BeginPlay();
}

void ACBP_AnimationType_SkillType::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (animationStart == false) return;

	curRotator = curRotator + (RotationSpeed * DeltaTime);
	SetActorRotation(curRotator);

	if (isNoCollision == true)
	{
		attackCollsiion->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		isNoCollision = false;
	}



}

void ACBP_AnimationType_SkillType::Play(bool const InSuccess, bool& Success)
{
	Super::Play(InSuccess, Success);

	KismetDelay(TEXT("AnimationStart"), this, delayTime);

}


void ACBP_AnimationType_SkillType::Animation(float const Alpha)
{
	FVector curWorldPos = FMath::Lerp(worldStartPosition, worldEndPosition, Alpha);
//	FRotator curWorldRotator = FMath::Lerp(startRotation, endRotation, Alpha);
	FVector curWorldScale = FMath::Lerp(startScale, endScale, Alpha);

	SetActorLocation(curWorldPos);
//	SetActorRotation(curWorldRotator);
	SetActorScale3D(curWorldScale);
}

void ACBP_AnimationType_SkillType::AnimationEnd()
{
	SetEnd();
	animationStart = false;
}

void ACBP_AnimationType_SkillType::AnimationStart()
{
	ThisClass::SetStart();
	animationStart = true;

}

void ACBP_AnimationType_SkillType::ResetAttack()
{
	OverlapedActors.Empty();
	attackCount++;

	isNoCollision = true;
	attackCollsiion->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (attackCount < AttackNumber)
	{
		KismetDelay(TEXT("ResetAttack"), this, ResetTime);
	}
	
}

void ACBP_AnimationType_SkillType::SetStart()
{
	if (attackCollsiion != nullptr)
		attackCollsiion->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	
	animationTimeLine->Play();
	particle->BeginTrails(Trail_Start, Trail_End, ETrailWidthMode::ETrailWidthMode_FromCentre, 1.0f);

	attackCount = 1;
	if (ResetTime > 0 && attackCount < AttackNumber)
	{
		KismetDelay(TEXT("ResetAttack"), this, ResetTime);
	}
}

void ACBP_AnimationType_SkillType::SetEnd()
{
	particle->EndTrails();

	if (destroyTime == 0)
	{
		DestroyActor(this);
	}
	else
	{
		KismetDelay(TEXT("DestroyThisActor"), this, destroyTime);
	}

}
void ACBP_AnimationType_SkillType::DestroyThisActor()
{
	DestroyActor(this);
}


void ACBP_AnimationType_SkillType::SetMesh(EMeshType newMeshType)
{
	Super::SetMesh(newMeshType);

	SetAttachRules(Rules);

	CreateDefaultSubobjectAuto(particle);
	CreateDefaultSubobjectAuto(animationTimeLine);

	switch (meshType)
	{
	case EMeshType::StaticMesh:
		particle->SetupAttachment(staticMesh);
		break;
	case EMeshType::SkeletalMesh:
		particle->SetupAttachment(skeletalMesh);
		break;
	}

	switch (attackCollisionType)
	{
	case ECollisionType::Box:
		attackCollsiion = CreateDefaultSubobject<UBoxComponent>(FName("attackCollsiion"));
		break;
	case ECollisionType::Sphere:
		attackCollsiion = CreateDefaultSubobject<USphereComponent>(FName("attackCollsiion"));
		break;
	case ECollisionType::Capsule:
		attackCollsiion = CreateDefaultSubobject<UCapsuleComponent>(FName("attackCollsiion"));
		break;
	}

	if (attackCollsiion != nullptr)
	{
		switch (meshType)
		{
		case EMeshType::StaticMesh:
			attackCollsiion->SetupAttachment(staticMesh);
			break;
		case EMeshType::SkeletalMesh:
			attackCollsiion->SetupAttachment(skeletalMesh);
			break;
		}

		attackCollsiion->SetCollisionProfileName(FName("Attack"));
		attackCollsiion->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		attackCollsiion->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentBeginOverlap);
	}
}

void ACBP_AnimationType_SkillType::SetSpawn(AActor* centerActor)
{
//	Super::SetSpawn(LocalStartPosition, LocalEndPosition, AttackTarget);

	AActor* result_CenterActor = centerActor;

	if (centerActor == nullptr) result_CenterActor = GetInstigator();

	if (GetInstigator() == nullptr) return;
	

	/*
	skill에서 가지고있는것 -> worldStartPos, worldEndPos; startRot; , startScale
	추가로 필요한것 -> endRot, endScale

	기본적으로 입력받은것 -> Local StartPos, LocalEndPos, Local StartRot, Local startScale
	필요한것 -> Local endRot, Local EndScale;
	*/

	FVector InstigatorForward = result_CenterActor->GetActorForwardVector();
	FVector InstigatorUp = result_CenterActor->GetActorUpVector();
	FVector InstigatorRight = result_CenterActor->GetActorRightVector();

	worldStartPosition = InstigatorForward * centerStartPos.X +
		InstigatorUp * centerStartPos.Z +
		InstigatorRight * centerStartPos.Y;

	worldStartPosition += result_CenterActor->GetActorLocation();

	worldEndPosition = InstigatorForward * centerEndPos.X +
		InstigatorUp * centerEndPos.Z +
		InstigatorRight * centerEndPos.Y;

	worldEndPosition += result_CenterActor->GetActorLocation();

	SetActorLocation(worldStartPosition);

	startRotation = UKismetMathLibrary::FindLookAtRotation(FVector(0, 0, 0), centerStartLookVector);
	startRotation.Roll += centerStartRoll;
	startRotation += result_CenterActor->GetActorRotation();
	SetActorRotation(startRotation);

//	endRotation = centerEndRotator + startRotation;

	RotationSpeed = centerEndRotator * (1 / animationTime);
	curRotator = startRotation;

	SetActorScale3D(centerStartScale);
	startScale = centerStartScale;
	endScale = centerEndScale;

	switch (meshType)
	{
	case EMeshType::StaticMesh:
		staticMesh->SetRelativeLocation(meshStartRelativeLocation);
		staticMesh->SetRelativeRotation(meshStartRot);
		staticMesh->SetRelativeScale3D(meshStartScale);
		break;
	case EMeshType::SkeletalMesh:
		skeletalMesh->SetRelativeLocation(meshStartRelativeLocation);
		skeletalMesh->SetRelativeRotation(meshStartRot);
		skeletalMesh->SetRelativeScale3D(meshStartScale);
		break;
	}

	if (AnimationCurve != nullptr)
	{
		FOnTimelineFloat OnAnimation;
		OnAnimation.BindDynamic(this, &ThisClass::Animation);
		animationTimeLine->AddInterpFloat(AnimationCurve, OnAnimation);

		if (animationTime == 0)
		{
			animationTimeLine->SetPlayRate(1);
		}
		else
		{
			animationTimeLine->SetPlayRate(1 / animationTime);
		}

		FOnTimelineEvent endEvent;
		endEvent.BindDynamic(this, &ThisClass::AnimationEnd);
		animationTimeLine->SetTimelineFinishedFunc(endEvent);
	}

	if (AttackNumber <= 0)
		AttackNumber = 1;

	ResetTime = animationTime / AttackNumber;

}
