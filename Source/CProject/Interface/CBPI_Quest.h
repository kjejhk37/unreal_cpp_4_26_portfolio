// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CBPI_Quest.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCBPI_Quest : public UInterface
{
	GENERATED_BODY()
};


class CPROJECT_API ICBPI_Quest
{
	GENERATED_BODY()

public:
	virtual void StartQuest() PURE_VIRTUAL(ICBPI_Quest::StartQuest, return;);
	virtual void EndQuest() PURE_VIRTUAL(ICBPI_Quest::EndQuest, return;);

	virtual void MissionSuccess(AActor* interactionActor) PURE_VIRTUAL(ICBPI_Quest::MissionSuccess, return;);
	virtual void StageClear(AActor* StageActor) PURE_VIRTUAL(ICBPI_Quest::StageClear, return;);

	virtual void SpawnNextQuest() PURE_VIRTUAL(ICBPI_Quest::SpawnNextQuest, return;);

};
