// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/NS_InteractionObject/CBP_NS_InteractionObject.h"
#include "Character/AICharacter/CBP_AICharacter.h"
#include "../PortalObject/CBP_PortalObject.h"

#include "Interface/CBPI_SpawnerActor.h"
#include "Struct/SInteraction.h"

#include "CBP_StageStart_Object.generated.h"


UCLASS()
class CPROJECT_API ACBP_StageStart_Object : public ACBP_NS_InteractionObject , public ICBPI_SpawnerActor
{
	GENERATED_BODY()
	
public:
	ACBP_StageStart_Object();
	void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
protected:
	void Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType) override;
	virtual void Tick(float DeltaTime) override;
public:
	// CBPI_Interaction 인터페이스
	void Interaction(AActor* const InteractionActor, bool& Success, AActor*& ResultActor) override;
	void SetLock(bool inLock) override;

	void SetSpawnerActor(AActor* InSpawnedActor)override;
	void SetDeleteSpawnedActor(AActor* InDeleteSpawnedActor)override;


	UPROPERTY(EditAnywhere, Category = "Set") TArray<F_SpawnMonsterStageData> allStageData;
	UPROPERTY(EditAnywhere, Category = "Set") TArray<AActor*> WillLockActors;

	UPROPERTY(EditAnywhere, Category = "Set") float StageTime = 180;
protected:
	UPROPERTY(EditAnywhere, Category = "Set") class UParticleSystem* spawnParticle;

	UFUNCTION() void StartStage();
	UFUNCTION() void EndStage();

private:

	int curStage = 0;
	int maxStage = INT_MAX;
	TArray<AActor*> SpawnedActors;
	AActor* target;

};
