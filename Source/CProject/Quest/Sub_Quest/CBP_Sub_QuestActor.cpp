// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/Sub_Quest/CBP_Sub_QuestActor.h"

#include "Macro/MyMacro.h"
#include "Macro/KismetMacro.h"

#include "Logger/Logger.h"

ACBP_Sub_QuestActor::ACBP_Sub_QuestActor()
{

}

void ACBP_Sub_QuestActor::BeginPlay()
{
	Super::BeginPlay();
}

void ACBP_Sub_QuestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACBP_Sub_QuestActor::StartQuest()
{
	SetSpawnedAllActors();
	SetLinkActors();
	SetBeginPlayAllActors();
	SpawnSubQuest();

	if (ACBP_Player* player = Cast<ACBP_Player>(Questcharacter))
	{
		player->QuestInterfaceUpdate();
	}
}

void ACBP_Sub_QuestActor::EndQuest()
{
	Super::EndQuest();

}


void ACBP_Sub_QuestActor::MissionSuccess(AActor* interactionActor)
{
	Super::MissionSuccess(interactionActor);
}

void ACBP_Sub_QuestActor::StageClear(AActor* StageActor)
{
	Super::StageClear(StageActor);
}

void ACBP_Sub_QuestActor::SpawnNextQuest()
{
	if (nextQuests.IsValidIndex(0) == false)
	{
		SetDeleteSpawnedActors_All();

		if (upQuest != nullptr)upQuest->CompleteSubQuest(this);
		
		ACBP_Player* player = Cast<ACBP_Player>(Questcharacter);

		if (player != nullptr)
		{
			if (player->curQuestActors.Contains(this) == true)
			{
				player->curQuestActors.Remove(this);
				player->QuestInterfaceUpdate();
			}
		}

		DestroyActor(this);

		return;
	}

	if (Cast<ACBP_Sub_QuestActor>(nextQuests[0].GetDefaultObject()) == nullptr)
	{
		SetDeleteSpawnedActors_All();
		if (upQuest != nullptr)upQuest->CompleteSubQuest(this);

		DestroyActor(this);
		return;
	}

	SetDeleteSpawnedActors_Count();

	TSubclassOf<ACBP_QuestActor> nextQuestClass = nextQuests[0];
	nextQuests.RemoveAt(0);

	ACBP_Sub_QuestActor* nextQuestActor;
	FActorSpawnParameters param;

	SpawnActorUseClass(nextQuestActor, nextQuestClass, param);
	if (nextQuestActor != nullptr)
	{
		nextQuestActor->nextQuests = nextQuests;
		nextQuestActor->SpawnedKeys = SpawnedKeys;
		nextQuestActor->SpawnedPortals = SpawnedPortals;
		nextQuestActor->SpawnedRemotes = SpawnedRemotes;
		nextQuestActor->SpawnedStages = SpawnedStages;
		nextQuestActor->SpawnedAnimations = SpawnedAnimations;
		nextQuestActor->SpawnedChests = SpawnedChests;
		nextQuestActor->Questcharacter = Questcharacter;

		if (upQuest != nullptr)
		{
			nextQuestActor->SetUpQuest(upQuest);
			upQuest->AddSubQuestData(nextQuestActor);
		}
		nextQuestActor->StartQuest();
	}
	else
	{
		SetDeleteSpawnedActors_All();
	}


	if (upQuest != nullptr)upQuest->CompleteSubQuest(this);
	

	DestroyActor(this);

}

void ACBP_Sub_QuestActor::SetUpQuest(ACBP_QuestActor* newUpQuest)
{ 
	upQuest = newUpQuest;

	SubQuestDeepLevel = 1;

	if (ACBP_Sub_QuestActor* upSubQuest = Cast<ACBP_Sub_QuestActor>(upQuest))
	{
		SubQuestDeepLevel = upSubQuest->SubQuestDeepLevel + 1;
	}

}