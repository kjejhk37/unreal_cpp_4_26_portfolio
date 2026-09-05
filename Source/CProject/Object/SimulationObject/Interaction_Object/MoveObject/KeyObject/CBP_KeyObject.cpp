// Fill out your copyright notice in the Description page of Project Settings.


#include "CBP_KeyObject.h"
#include "Components/ShapeComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include "Macro/MyMacro.h"

ACBP_KeyObject::ACBP_KeyObject()
{

}

void ACBP_KeyObject::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}


void ACBP_KeyObject::BeginPlay()
{
	Super::BeginPlay();

	for (AActor* actor : WillLockActors)
	{
		ICBPI_Interaction* interactionActor = Cast<ICBPI_Interaction>(actor);
		if (interactionActor == nullptr) continue;

		interactionActor->SetKey(this);
	}
}

void ACBP_KeyObject::Set_Simul_ComponentsBase(EMeshType newMeshType, ESimulationType newSimulationType, ECollisionType newInteractionType)
{
	Super::Set_Simul_ComponentsBase(newMeshType, newSimulationType, newInteractionType);

}

void ACBP_KeyObject::Interaction(AActor* const InteractionActor, bool& Success, AActor*& ResultActor)
{
	Super::Interaction(InteractionActor, Success, ResultActor);

	Success = false;
	if (isLock == true) return;

	for (AActor* actor : WillLockActors)
	{
		ICBPI_Interaction* interactionActor = Cast<ICBPI_Interaction>(actor);
		if (interactionActor == nullptr) continue;

		bool isLocked = false;
		interactionActor->IsLockedKey(this, isLocked);

		if (isLocked)
		{
			bool outSuccess;
			interactionActor->OpenKey(this, outSuccess);
		}
		else
		{
			interactionActor->SetKey(this);
		}
	}

	SetOnceInteraction();
	Success = true;
	InteractionParticle->Activate(true);
}

void ACBP_KeyObject::SetLock(bool inLock)
{
	Super::SetLock(inLock);
}

