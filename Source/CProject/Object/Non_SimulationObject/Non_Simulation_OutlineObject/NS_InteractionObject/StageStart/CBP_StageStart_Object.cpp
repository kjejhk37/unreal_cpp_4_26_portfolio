// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/NS_InteractionObject/StageStart/CBP_StageStart_Object.h"
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

ACBP_StageStart_Object::ACBP_StageStart_Object()
{
	PrimaryActorTick.bCanEverTick = true;
	Set_NonSimul_ComponentsBase(EMeshType::StaticMesh, ECollisionType::Sphere);
}

void ACBP_StageStart_Object::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}

void ACBP_StageStart_Object::BeginPlay()
{
	Super::BeginPlay();

	maxStage = allStageData.Num() - 1;

}

void ACBP_StageStart_Object::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACBP_StageStart_Object::Interaction(AActor* const InteractionActor, bool& Success, AActor*& ResultActor)
{
	Super::Interaction(InteractionActor, Success, ResultActor);

	if (isLock == true) return;

	ACBP_Player* player = Cast<ACBP_Player>(InteractionActor);
	if (player == nullptr) return;

	target = player;
	curStage = 0;

	interactionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	for (AActor* actor : WillLockActors)
	{
		ICBPI_Interaction* interactionActor = Cast<ICBPI_Interaction>(actor);
		if (interactionActor == nullptr) continue;

		interactionActor->SetKey(this);
	}

	StartStage();
	InteractionParticle->Activate(true);
	Success = true;
	ResultActor = nullptr;

}


void ACBP_StageStart_Object::Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType)
{
	Super::Set_NonSimul_ComponentsBase(newMeshType, newInteractionType);

}

void ACBP_StageStart_Object::SetLock(bool inLock)
{
	Super::SetLock(inLock);
}

void ACBP_StageStart_Object::StartStage()
{
	if (allStageData.IsValidIndex(curStage) == false)
	{
		EndStage();
		return;
	}
	TArray<F_SpawnMonsterData> eachStageData = allStageData[curStage].eachStageDatas;

	for (F_SpawnMonsterData data : eachStageData)
	{
		ACBP_AICharacter* character;
		FActorSpawnParameters param;
		
		character = GetWorld()->SpawnActor<ACBP_AICharacter> (data.SpawnChatracter,FVector(10000,10000,10000),FRotator(0,0,0));
//		SpawnActorUseClass(character, data.SpawnChatracter, param);
		if (character == nullptr) continue;

		character->SpawnerActor = this;
		character->SetActorLocation(data.SpawnPos + FVector(0,0,100));
		character->SetActorRotation(data.SpawnRotator);

		character->targetCandidate.Add(target);

		character->SpawnDefaultController();

		character->SetSpawnLifeTime(StageTime);

		character->SerchCloseTarget();

		if (spawnParticle != nullptr)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), spawnParticle, data.SpawnPos,
				FRotator(0, 0, 0), FVector(1, 1, 1), true);
		}

		SpawnedActors.Add(character);
	}
}

void ACBP_StageStart_Object::EndStage()
{
	for (AActor* actor : WillLockActors)
	{
		ICBPI_Interaction* interactionActor = Cast<ICBPI_Interaction>(actor);
		if (interactionActor == nullptr) continue;

		bool outSuccess;
		interactionActor->OpenKey(this, outSuccess);
	}

	if (spawnParticle != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), spawnParticle, GetActorLocation(),
			FRotator(0, 0, 0), FVector(1, 1, 1), true);
	}

	for (AActor* actor : QuestActors)
	{
		ACBP_QuestActor* quest = Cast<ACBP_QuestActor>(actor);
		if (quest == nullptr)
		{
			QuestActors.Remove(actor);
			return;
		}

		quest->StageClear(this);
	}

	DestroyActor(this);
}

void ACBP_StageStart_Object::SetSpawnerActor(AActor* InSpawnedActor)
{
	SpawnedActors.Add(InSpawnedActor);
}

void ACBP_StageStart_Object::SetDeleteSpawnedActor(AActor* InDeleteSpawnedActor)
{
	if (SpawnedActors.Contains(InDeleteSpawnedActor) == true)
		SpawnedActors.Remove(InDeleteSpawnedActor);

	if (SpawnedActors.Num() == 0)
	{
		if (curStage == maxStage)
		{
			EndStage();
		}
		else
		{
			curStage++;
			StartStage();
		}
	}

}