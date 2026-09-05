// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Non_SimulationObject/CBP_Non_SimulationObject.h"
#include "CBP_TerrainObject.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API ACBP_TerrainObject : public ACBP_Non_SimulationObject
{
	GENERATED_BODY()

public:
	ACBP_TerrainObject();

	void Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType) override;

	virtual void BeginPlay() override;
public:
	UPROPERTY(VisibleAnywhere) class UBoxComponent* TerrainCollision;

};
