// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Quest/Sub_Quest/CBP_Sub_QuestActor.h"
#include "CBP_StageClear_Sub_QuestActor.generated.h"

USTRUCT(BlueprintType)
struct F_QuestActor_CheckStage
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TArray<EStageNameType> StageNameTyps;

};

UCLASS()
class CPROJECT_API ACBP_StageClear_Sub_QuestActor : public ACBP_Sub_QuestActor
{
	GENERATED_BODY()

public:
	ACBP_StageClear_Sub_QuestActor();

	void StartQuest() override;
	void StageClear(AActor* StageActor) override;
protected:
	void SetCheckStages();

	UPROPERTY(EditDefaultsOnly, Category = "Set") TMap<int, F_QuestActor_CheckStage> checkStages;
	TArray<AActor*> will_CheckStage;

	
};
