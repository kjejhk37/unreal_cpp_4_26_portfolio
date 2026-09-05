// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Quest/CBP_QuestActor.h"
#include "CBP_Sub_QuestActor.generated.h"


UCLASS()
class CPROJECT_API ACBP_Sub_QuestActor : public ACBP_QuestActor
{
	GENERATED_BODY()

public:
	ACBP_Sub_QuestActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	void StartQuest() override;
	void EndQuest() override;
	void MissionSuccess(AActor* interactionActor) override;
	void StageClear(AActor* StageActor) override;

	void SpawnNextQuest() override;

	void SetUpQuest(ACBP_QuestActor* newUpQuest);

	int SubQuestDeepLevel = 0;
public:
	ACBP_QuestActor* upQuest = nullptr;
	

};
