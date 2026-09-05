// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CBP_SimulationOutlineObject.h"
#include "Enums/EObject.h"
#include "Interface/CBPI_Interaction.h"
#include "CBP_Interaction_Object.generated.h"

UCLASS(Abstract)
class CPROJECT_API ACBP_Interaction_Object : 
	public ACBP_SimulationOutlineObject,
	public ICBPI_Interaction
{
	GENERATED_BODY()

public:
	ACBP_Interaction_Object();
	void OnConstruction(const FTransform& Transform) override;
	//	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	void Set_Simul_ComponentsBase(EMeshType newMeshType, ESimulationType newSimulationType, ECollisionType newInteractionType)override;

public:
	// CBPI_Interaction 인터페이스
	void Interaction(AActor* const InteractionActor, bool& Success, AActor*& ResultActor) override;
	void SetLock(bool inLock) override;

	bool GetisLock() { return isLock; }
	void SetQuest(AActor* QuestActor) override;


	void OpenKey(AActor* keyObject, bool& Success)override;
	void SetKey(AActor* keyObject)override;
	void IsLockedKey(AActor* keyObject, bool& LockedKey)override;

	UPROPERTY(EditAnywhere,Category = "Setting") FString widgetName = FString("InteractionObject");
public:
	UFUNCTION(BlueprintCallable,Category = "Set")void SetInteractionCollision(ECollisionEnabled::Type const newCollisionType);

	void SetOnceInteraction();
protected:
	UPROPERTY(VisibleAnyWhere) class UShapeComponent* interactionComponent;
	UPROPERTY(VisibleAnyWhere) class UParticleSystemComponent* LockParticle;
	UPROPERTY(VisibleAnyWhere) class UParticleSystemComponent* InteractionParticle;

	UPROPERTY(BlueprintReadOnly, Category = "Type")ECollisionType interactionType;

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Set") bool DirectInputType = true;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Set") bool isOnceInteraction = false;
	
protected:
	bool isLock = false;
	UPROPERTY(BlueprintReadOnly) TArray<AActor*> keys;

	TArray<AActor*> QuestActors;
	
};
