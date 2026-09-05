// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/NS_InteractionObject/QuestStart/CBP_QuestStartObject.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ShapeComponent.h"

#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

#include "Character/Player/CBP_Player.h"
#include "Quest/CBP_QuestActor.h"

#include "Macro/MyMacro.h"

#include "Logger/Logger.h"


ACBP_QuestStartObject::ACBP_QuestStartObject()
{
	Set_NonSimul_ComponentsBase(EMeshType::StaticMesh, ECollisionType::Sphere);
}

void ACBP_QuestStartObject::BeginPlay()
{
	Super::BeginPlay();
}

void ACBP_QuestStartObject::Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType)
{
	Super::Set_NonSimul_ComponentsBase(newMeshType, newInteractionType);
}

void ACBP_QuestStartObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACBP_QuestStartObject::Interaction(AActor* const InteractionActor, bool& Success, AActor*& ResultActor)
{
	Super::Interaction(InteractionActor, Success, ResultActor);

	if (isLock == true) return;
	ACBP_Player* player = Cast<ACBP_Player>(InteractionActor);
	if (player == nullptr) return;

	if (questActorClass != nullptr)
	{
		ACBP_QuestActor* questActor;
		FActorSpawnParameters param;

		SpawnActorUseClass(questActor, questActorClass, param);

		questActor->Questcharacter = player;
		player->curQuestActors.AddUnique(questActor);

		questActor->StartQuest();
	}

	interactionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	InteractionParticle->Activate(true);
	Success = true;
	ResultActor = nullptr;

	DestroyActor(this);
	
}

void ACBP_QuestStartObject::SetLock(bool inLock)
{
	Super::SetLock(inLock);
}