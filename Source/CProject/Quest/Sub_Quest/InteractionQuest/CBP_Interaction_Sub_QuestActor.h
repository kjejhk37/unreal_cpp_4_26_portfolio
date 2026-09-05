// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Quest/Sub_Quest/CBP_Sub_QuestActor.h"
#include "CBP_Interaction_Sub_QuestActor.generated.h"

USTRUCT(BlueprintType)
struct F_QuestActor_CheckInteractions
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TArray<EKeyNameTypes> KeyNameTyps;
	UPROPERTY(EditAnywhere) TArray<EPortalNameTypes> PortalNameTyps;
	UPROPERTY(EditAnywhere) TArray<ERemoteNameType> RemoteNameTyps;
	UPROPERTY(EditAnywhere) TArray<EStageNameType> StageNameTyps;
	UPROPERTY(EditAnywhere) TArray<EAnimationNameType> AnimationNameTyps;
	UPROPERTY(EditAnywhere) TArray<EChestNameType> ChestNameTyps;
};


UCLASS()
class CPROJECT_API ACBP_Interaction_Sub_QuestActor : public ACBP_Sub_QuestActor
{
	GENERATED_BODY()

public:
	ACBP_Interaction_Sub_QuestActor();

	void StartQuest() override;
	void MissionSuccess(AActor* interactionActor) override;

protected:
	void SetCheckInteraction();

	UPROPERTY(EditDefaultsOnly, Category = "Set") TMap<int, F_QuestActor_CheckInteractions> checkInteractions;
	TArray<AActor*> will_CheckInteractions;


};
