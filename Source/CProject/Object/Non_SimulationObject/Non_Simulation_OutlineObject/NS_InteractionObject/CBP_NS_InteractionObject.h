// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/CBP_NS_OutlineObject.h"
#include "Interface/CBPI_Interaction.h"
#include "CBP_NS_InteractionObject.generated.h"


UCLASS()
class CPROJECT_API ACBP_NS_InteractionObject : 
	public ACBP_NS_OutlineObject,
	public ICBPI_Interaction
{
	GENERATED_BODY()

public:
	ACBP_NS_InteractionObject();
	void OnConstruction(const FTransform& Transform) override;
protected:
	void Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType) override;
	virtual void BeginPlay() override;
	
public:
	// CBPI_Interaction 인터페이스
	void Interaction(AActor* const InteractionActor, bool& Success, AActor*& ResultActor) override;
	void SetLock(bool inLock) override;

	bool GetisLock() { return isLock; }
	void SetQuest(AActor* QuestActor)override;

	void OpenKey(AActor* keyObject, bool& Success)override;
	void SetKey(AActor* keyObject)override;
	void IsLockedKey(AActor* keyObject, bool& LockedKey)override;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Setting") FString widgetName = FString("NS_InteractionObject");

	void SetOnceInteraction();
protected:
	UPROPERTY(VisibleAnyWhere) class UShapeComponent* interactionComponent;
	UPROPERTY(VisibleAnyWhere) class UParticleSystemComponent* LockParticle;
	UPROPERTY(VisibleAnyWhere) class UParticleSystemComponent* InteractionParticle;

	UPROPERTY(BlueprintReadOnly, Category = "Type")ECollisionType interactionType;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Set") bool isOnceInteraction = false;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Set") bool DirectInputType = true;

protected:
	bool isLock = false;
	UPROPERTY(BlueprintReadOnly) TArray<AActor*> keys;

protected:
	TArray<AActor*> QuestActors;

};
