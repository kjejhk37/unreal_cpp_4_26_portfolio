// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/NS_InteractionObject/Animation_Object/Remote/CBP_RemoteObject.h"
#include "Components/ShapeComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include "Character/Player/CBP_Player.h"

#include "Macro/IncludeMacro.h"

#include MainWeaponPath
#include PairWeaponPath
#include "Skill/CBP_Skill.h"
#include "Quest/CBP_QuestActor.h"

#include "Logger/Logger.h"

#include "Macro/MyMacro.h"


ACBP_RemoteObject::ACBP_RemoteObject()
{
	Set_NonSimul_ComponentsBase(EMeshType::StaticMesh, ECollisionType::Sphere);

}

void ACBP_RemoteObject::BeginPlay()
{
	Super::BeginPlay();

	interactionComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentBeginOverlap);
}

void ACBP_RemoteObject::Interaction(AActor* const InteractionActor, bool& Success, AActor*& ResultActor)
{
	if (isLock == true) return;

	ACBP_Player* player = Cast<ACBP_Player>(InteractionActor);
	if (player == nullptr)return;

	for (AActor* actor : RemoteTargetActors)
	{
		if (IsValid(actor) == false)
		{
			RemoteTargetActors.Remove(actor);
			continue;
		}

		if (ICBPI_Interaction* interactionActor = Cast<ICBPI_Interaction>(actor))
		{
			interactionActor->Interaction(InteractionActor, Success, ResultActor);
		}
	}

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

	Success = true;
	InteractionParticle->Activate(true);
	SetOnceInteraction();
}

void ACBP_RemoteObject::SetLock(bool inLock)
{
	Super::SetLock(inLock);
}

void ACBP_RemoteObject::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (overlapedActors.Contains(OtherActor) == true) return;
	overlapedActors.Add(OtherActor);

	bool Success;
	AActor* result;

	if (auto* actor = Cast<ACBP_MainWeapon>(OtherActor))
	{
		Interaction(actor->GetInstigator(), Success, result);
		return;
	}

	if (auto* actor = Cast<ACBP_PairWeapon>(OtherActor))
	{
		Interaction(actor->GetInstigator(), Success, result);
		return;
	}

	if (auto* skill = Cast<ACBP_Skill>(OtherActor))
	{
		Interaction(skill->GetInstigator(), Success, result);
		return;
	}
}

