// Fill out your copyright notice in the Description page of Project Settings.


#include "CBP_AnimationObject.h"
#include "Components/ShapeComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include "Components/TimelineComponent.h"
#include "Character/Player/CBP_PlayerController.h"
#include "Quest/CBP_QuestActor.h"

#include "Macro/MyMacro.h"
#include "Macro/KismetMacro.h"

#include "UI/WCBP_TextBase.h"

#include "Logger/Logger.h"

ACBP_AnimationObject::ACBP_AnimationObject()
{
	CreateDefaultSubobjectAuto(AnimationTimeLine);

}
	
void ACBP_AnimationObject::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}

void ACBP_AnimationObject::Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType)
{
	CreateDefaultSubobjectAuto(center);
	SetRootComponent(center);

	Super::Set_NonSimul_ComponentsBase(newMeshType, newInteractionType);
	CreateDefaultSubobjectAuto(parkourAnimationObject);

	switch (meshType)
	{
	case EMeshType::StaticMesh:
		staticMesh->SetupAttachment(center);
		parkourAnimationObject->SetupAttachment(staticMesh);
		staticMesh->SetCollisionProfileName(FName("Terrain"));
		break;
	case EMeshType::SkeletalMesh:
		skeletalMesh->SetupAttachment(center);
		parkourAnimationObject->SetupAttachment(skeletalMesh);
		skeletalMesh->SetCollisionProfileName(FName("Terrain"));
		break;
	}


}

void ACBP_AnimationObject::BeginPlay()
{
	Super::BeginPlay();

	if (BlendCurveOnAnimation != nullptr && isOnceBind == false)
	{
		isOnceBind = true;
		FOnTimelineFloat OnAnimation;
		OnAnimation.BindDynamic(this, &ThisClass::Animation);
		AnimationTimeLine->AddInterpFloat(BlendCurveOnAnimation, OnAnimation);
	}

	if (isOnceBind == true)
	{
		AnimationTimeLine->SetPlayRate(1/playTime);
	}

	ActorStartRotator = GetActorRotation();
	TempActorEndRotator = ActorStartRotator + ActorEndRotator;

}

void ACBP_AnimationObject::OpenKey(AActor* keyObject, bool& Success)
{
	Super::OpenKey(keyObject, Success);

	if (keys.Num() == 0)
	{
		canOpen = true;
		isPlay = false;
	}

}


void ACBP_AnimationObject::Interaction(AActor* const InteractionActor, bool& Success, AActor*& ResultActor)
{
	FString str = FString(widgetName);

	Success = false;
	if (isLock == true || canOpen == false)
	{
		str += FString(" can't interact ");
	}
	else
	{
		if (isPlay == false)
		{
			AnimationTimeLine->Play();
			isPlay = true;
		}
		else
		{
			AnimationTimeLine->Reverse();
			isPlay = false;
		}

		SetOnceInteraction();
		str += FString(" interacted with ");
		Success = true;
		InteractionParticle->Activate();

		TArray<AActor*> willDeleteActor;

		for (AActor* actor : QuestActors)
		{
			ACBP_QuestActor* quest = Cast<ACBP_QuestActor>(actor);
			if (quest == nullptr)
			{
				willDeleteActor.Add(actor);
				continue;
			}
			
			if(quest != nullptr)
			{
				quest->MissionSuccess(this);
			}
		}

		for (AActor* deleteActor : willDeleteActor)
		{
			if (QuestActors.Contains(deleteActor) == true)
			{
				QuestActors.Remove(deleteActor);
			}
		}
	}



	ACBP_PlayerController* playerController = Cast<ACBP_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (playerController == nullptr) return;
	playerController->Interface_TextDraw(FName(widgetName), str, FVector2D(0, -250), true, 1, FVector2D(0, -50));

}

void ACBP_AnimationObject::SetLock(bool inLock)
{
	Super::SetLock(inLock);

	canOpen = !isLock;	
}

void ACBP_AnimationObject::Animation(float const Alpha)
{
	switch (meshType)
	{
	case EMeshType::StaticMesh:
		staticMesh->SetRelativeTransform(UKismetMathLibrary::TLerp(StartTransform, EndTransform, Alpha),false);
		break;
	case EMeshType::SkeletalMesh:
		skeletalMesh->SetRelativeTransform(UKismetMathLibrary::TLerp(StartTransform, EndTransform, Alpha),false);
		break;
	}

	SetActorRotation(UKismetMathLibrary::RLerp(ActorStartRotator, TempActorEndRotator, Alpha,true));

}
