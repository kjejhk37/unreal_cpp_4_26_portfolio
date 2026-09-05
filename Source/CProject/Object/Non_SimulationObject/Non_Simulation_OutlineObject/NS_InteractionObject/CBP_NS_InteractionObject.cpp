// Fill out your copyright notice in the Description page of Project Settings.


#include "CBP_NS_InteractionObject.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ShapeComponent.h"

#include "Macro/MyMacro.h"

#include "Character/Player/CBP_Player.h"
#include "Quest/CBP_QuestActor.h"

#include "Particles/ParticleSystemComponent.h"

ACBP_NS_InteractionObject::ACBP_NS_InteractionObject()
{

}

void ACBP_NS_InteractionObject::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}

void ACBP_NS_InteractionObject::BeginPlay()
{
	Super::BeginPlay();

	if (DirectInputType == false)
	{
		interactionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	
}

void ACBP_NS_InteractionObject::Interaction(AActor* const InteractionActor, bool& Success, AActor*& ResultActor)
{
	ResultActor = InteractionActor;

	TArray<AActor*> willDeletes;


	for (AActor* actor : QuestActors)
	{
		ACBP_QuestActor* quest = Cast<ACBP_QuestActor>(actor);
		if (quest == nullptr)
		{
			willDeletes.Add(actor);
			continue;
		}
		
		if(quest != nullptr)
		{ 
			if (IsValid(quest) == true)
			{
				quest->MissionSuccess(this);
			}
		}
	}

	for (AActor* willDelete : willDeletes)
	{
		if (QuestActors.Contains(willDelete) == true)
		{
			QuestActors.Remove(willDelete);
		}
	}

}

/* ================================ Set Base Component ==================================*/
void ACBP_NS_InteractionObject::Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType)
{
	Super::Set_NonSimul_ComponentsBase(newMeshType, newInteractionType);
	interactionType = newInteractionType;

	CreateDefaultSubobjectAuto(InteractionParticle);
	CreateDefaultSubobjectAuto(LockParticle);

	if (interactionType != ECollisionType::None)
	{

		switch (interactionType)
		{
		case ECollisionType::Box:
			interactionComponent = Cast<UShapeComponent>(CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction")));
			break;
		case ECollisionType::Sphere:
			interactionComponent = Cast<UShapeComponent>(CreateDefaultSubobject<USphereComponent>(TEXT("Interaction")));
			break;
		case ECollisionType::Capsule:
			interactionComponent = Cast<UShapeComponent>(CreateDefaultSubobject<UCapsuleComponent>(TEXT("Interaction")));
			break;
		}

		FAttachmentTransformRules const Rules(EAttachmentRule::KeepRelative, true);

		switch (meshType)
		{
		case EMeshType::StaticMesh:
			interactionComponent->AttachToComponent(staticMesh, Rules);
			break;
		case EMeshType::SkeletalMesh:
			interactionComponent->AttachToComponent(skeletalMesh, Rules);
			break;
		}

		interactionComponent->SetCollisionProfileName(FName("Interaction"));
		LockParticle->SetupAttachment(interactionComponent);
		InteractionParticle->SetupAttachment(interactionComponent);
	}

}

void ACBP_NS_InteractionObject::SetLock(bool inLock)
{
	isLock = inLock;

	if (isLock == true)
	{
		SetHiddenOutline(true);
		interactionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		LockParticle->Activate();
	}
	else
	{
		SetHiddenOutline(false);
		if (DirectInputType == true)
		{
			interactionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}
		LockParticle->Deactivate();

	}
}

void ACBP_NS_InteractionObject::SetOnceInteraction()
{
	if (isOnceInteraction == true)
		SetLock(true);
}

void ACBP_NS_InteractionObject::OpenKey(AActor* keyObject, bool& Success)
{
	Success = false;

	if (keys.Contains(keyObject) == true)
	{
		keys.Remove(keyObject);
		Success = true;

		if (keys.Num() == 0)
		{
			SetLock(false);
		}
	}

}

void ACBP_NS_InteractionObject::SetKey(AActor* keyObject)
{
	if (keys.Contains(keyObject) == false)
	{
		keys.Add(keyObject);
		SetLock(true);
	}
}

void ACBP_NS_InteractionObject::IsLockedKey(AActor* keyObject, bool& LockedKey)
{
	LockedKey = keys.Contains(keyObject);
}

void ACBP_NS_InteractionObject::SetQuest(AActor* QuestActor)
{
	QuestActors.AddUnique(QuestActor);
}
