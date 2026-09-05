// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Non_SimulationObject/CBP_Non_SimulationObject.h"
#include "CBP_NS_OutlineObject.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API ACBP_NS_OutlineObject : public ACBP_Non_SimulationObject
{
	GENERATED_BODY()

public:
	ACBP_NS_OutlineObject();
	void OnConstruction(const FTransform& Transform) override;
protected:
	void Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType) override;
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Set") void SetHiddenOutline(bool const newHidden);

protected:
	UFUNCTION(BlueprintCallable, Category = "Set Base") void SetOutline();
	
	UPROPERTY(VisibleAnyWhere) class USkeletalMeshComponent* skeletalOutlineMesh;
	UPROPERTY(VisibleAnyWhere) class UStaticMeshComponent* staticOutlineMesh;

	bool isOnce = false;
};
