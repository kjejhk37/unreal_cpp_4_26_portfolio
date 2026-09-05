// Fill out your copyright notice in the Description page of Project Settings.


#include "CBP_Interaction_Object.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ShapeComponent.h"

#include "Macro/MyMacro.h"

#include "Character/Player/CBP_Player.h"
#include "Quest/CBP_QuestActor.h"

#include "Particles/ParticleSystemComponent.h"

ACBP_Interaction_Object::ACBP_Interaction_Object()
{

}

void ACBP_Interaction_Object::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ACBP_Interaction_Object::BeginPlay()
{
	Super::BeginPlay();

	if (DirectInputType == false)
	{
		interactionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

}

/* ========================= Interaction Interface ========================*/
void ACBP_Interaction_Object::Interaction(AActor* const InteractionActor, bool& Success, AActor*& ResultActor)
{
	ResultActor = InteractionActor;

	for (AActor* actor : QuestActors)
	{
		ACBP_QuestActor* quest = Cast<ACBP_QuestActor>(actor);
		if (quest == nullptr)
		{
			QuestActors.Remove(actor);
			return;
		}

		quest->MissionSuccess(this);
	}

}

/*========================== Set ==========================================*/
void ACBP_Interaction_Object::SetInteractionCollision(ECollisionEnabled::Type const newCollisionType)
{
	interactionComponent->SetCollisionEnabled(newCollisionType);
}

/* ========================= Set Component Base ===========================*/

void ACBP_Interaction_Object::Set_Simul_ComponentsBase(EMeshType newMeshType, ESimulationType newSimulationType, ECollisionType newInteractionType)
{
	Super::Set_Simul_ComponentsBase(newMeshType, newSimulationType, newInteractionType);
	interactionType = newInteractionType;
	CreateDefaultSubobjectAuto(InteractionParticle);

	CreateDefaultSubobjectAuto(LockParticle);

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

	if (interactionComponent != nullptr)
	{
		interactionComponent->SetCollisionProfileName(FName("Interaction"));
		LockParticle->SetupAttachment(interactionComponent);
		InteractionParticle->SetupAttachment(interactionComponent);
	}

	if (simulationComponent != nullptr)
	{
		interactionComponent->SetupAttachment(simulationComponent);
	}
	else
	{
		switch (meshType)
		{
		case EMeshType::StaticMesh:
			interactionComponent->SetupAttachment(staticMesh);
			break;
		case EMeshType::SkeletalMesh:
			interactionComponent->SetupAttachment(skeletalMesh);
			break;
		}
	}

}

void ACBP_Interaction_Object::SetLock(bool inLock)
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

void ACBP_Interaction_Object::SetOnceInteraction()
{
	if (isOnceInteraction == true)
		SetLock(true);
}

void ACBP_Interaction_Object::OpenKey(AActor* keyObject, bool& Success)
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

void ACBP_Interaction_Object::SetKey(AActor* keyObject)
{
	if (keys.Contains(keyObject) == false)
	{
		keys.Add(keyObject);
		SetLock(true);
	}
}

void ACBP_Interaction_Object::IsLockedKey(AActor* keyObject, bool& LockedKey)
{
	LockedKey = keys.Contains(keyObject);
}

void ACBP_Interaction_Object::SetQuest(AActor* QuestActor)
{
	QuestActors.AddUnique(QuestActor);
}
