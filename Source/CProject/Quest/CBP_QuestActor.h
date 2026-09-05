// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Struct/SQuest.h"

#include "Character/Player/CBP_Player.h"

#include "Interface/CBPI_Quest.h"
#include "CBP_QuestActor.generated.h"

USTRUCT(BlueprintType)
struct F_QuestActor_DeleteCountStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) AActor* actor;
	UPROPERTY(EditAnywhere) int count = 0;
};



UCLASS()
class CPROJECT_API ACBP_QuestActor : public AActor ,public ICBPI_Quest
{
	GENERATED_BODY()
	
public:
	ACBP_QuestActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void StartQuest() override;
	void EndQuest() override;
	void MissionSuccess(AActor* interactionActor) override;
	void StageClear(AActor* StageActor) override;

	void SpawnNextQuest() override;

	void AddSubQuestData(ACBP_QuestActor* new_SubQuest);
	void CompleteSubQuest(ACBP_QuestActor* subQuest);
	void SpawnReward();

public:
	void SpawnSubQuest();
	void SpawnQuestActor(F_QuestActor_BaseStruct const data);
	void SpawnQuestActor(F_QuestActor_TextInterfaceStruct const data);
	void SpawnQuestActor(F_QuestActor_KeyStruct const data);
	void SpawnQuestActor(F_QuestActor_PortalStruct const data);
	void SpawnQuestActor(F_QuestActor_RemoteStruct const data);
	void SpawnQuestActor(F_QuestActor_StageStruct const data);
	void SpawnQuestActor(F_QuestActor_AnimationStruct const data);
	void SpawnQuestActor(F_QuestActor_ChestBoxStruct const data);
	void SpawnQuestActor(F_QuestActor_AttackTerrainStruct data);

	UPROPERTY(EditDefaultsOnly, Category = "SubQuest") FText QuestName;
	UPROPERTY(EditDefaultsOnly, Category = "EndDelayTime") float EndDelayTime = 5;

	UPROPERTY(EditDefaultsOnly, Category = "SubQuest") TArray<TSubclassOf<ACBP_QuestActor>> SubQuests;
	UPROPERTY(EditDefaultsOnly, Category = "nextQuest") TArray<TSubclassOf<ACBP_QuestActor>> nextQuests;
	UPROPERTY(EditDefaultsOnly, Category = "Reward") TArray<F_QuestActor_ChestBoxStruct> RewardChestBox;
	UPROPERTY(EditDefaultsOnly, Category = "Reward") TArray<F_QuestActor_BaseStruct> RewardActors;


	// 소환할 Actor들
	UPROPERTY(EditDefaultsOnly, Category = "QuestSpawnDatas") TArray<F_QuestActor_BaseStruct> SpawnActors;
	UPROPERTY(EditDefaultsOnly, Category = "QuestSpawnDatas") TArray<F_QuestActor_TextInterfaceStruct> SpawnTextInterfaceActors;
	UPROPERTY(EditDefaultsOnly, Category = "QuestSpawnDatas") TArray<F_QuestActor_AttackTerrainStruct> SpawnAttackTerrains;

	UPROPERTY(EditDefaultsOnly, Category = "QuestSpawnDatas") TMap<EKeyNameTypes,F_QuestActor_KeyStruct> SpawnKeys;
	UPROPERTY(EditDefaultsOnly, Category = "QuestSpawnDatas") TMap<EPortalNameTypes,F_QuestActor_PortalStruct> SpawnPotals;
	UPROPERTY(EditDefaultsOnly, Category = "QuestSpawnDatas") TMap<ERemoteNameType,F_QuestActor_RemoteStruct> SpawnRemotes;
	UPROPERTY(EditDefaultsOnly, Category = "QuestSpawnDatas") TMap<EStageNameType,F_QuestActor_StageStruct> SpawnStages;
	UPROPERTY(EditDefaultsOnly, Category = "QuestSpawnDatas") TMap<EAnimationNameType,F_QuestActor_AnimationStruct> SpawnAnimations;
	UPROPERTY(EditDefaultsOnly, Category = "QuestSpawnDatas") TMap<EChestNameType,F_QuestActor_ChestBoxStruct> SpawnChestBoxs;


public:
	// 소환된 Actor들
	TMap<EKeyNameTypes, F_QuestActor_DeleteCountStruct> SpawnedKeys;
	TMap<EPortalNameTypes, F_QuestActor_DeleteCountStruct> SpawnedPortals;
	TMap<ERemoteNameType, F_QuestActor_DeleteCountStruct> SpawnedRemotes;
	TMap<EStageNameType, F_QuestActor_DeleteCountStruct> SpawnedStages;
	TMap<EAnimationNameType, F_QuestActor_DeleteCountStruct> SpawnedAnimations;
	TMap<EChestNameType, F_QuestActor_DeleteCountStruct> SpawnedChests;

	TArray<F_QuestActor_DeleteCountStruct> SpawnedAttackTerrains;
	TArray<F_QuestActor_DeleteCountStruct> SpawnedNormalActor;
	TArray<F_QuestActor_DeleteCountStruct> SpawnedTextInterfaceActor;

	TArray<ACBP_QuestActor*> SpawnedSubQuests;

	ACBP_Player* Questcharacter;

protected:
	void SetDeleteSpawnedActors_Count();
	void SetDeleteSpawnedActors_All();

	void SetSpawnedAllActors();
	void SetLinkActors();
	void SetBeginPlayAllActors();

protected:
	UFUNCTION() void EndQuestDelayTime();


};
