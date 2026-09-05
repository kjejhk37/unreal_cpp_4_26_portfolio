// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/SimulationObject/Interaction_Object/CBP_Interaction_Object.h"
#include "Enums/EItem.h"
#include "CBP_ItemObject.generated.h"

UCLASS()
class CPROJECT_API ACBP_ItemObject : public ACBP_Interaction_Object
{
	GENERATED_BODY()

public:
	ACBP_ItemObject();
	void OnConstruction(const FTransform& Transform) override;
	//	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	void Set_Simul_ComponentsBase(EMeshType newMeshType, ESimulationType newSimulationType, ECollisionType newInteractionType)override;

public:
	// CBPI_Interaction Inferface
	void Interaction(AActor* const InteractionActor, bool& Success, AActor*& ResultActor) override;

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item") int itemNum;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item") EItemName itemName;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Setting") FString widgetString = FString("Default Item");


};
