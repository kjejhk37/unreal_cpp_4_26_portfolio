// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Non_SimulationObject/CBP_AttackTerrainObject.h"
#include "CBP_Normal_AttackTerrainObject.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API ACBP_Normal_AttackTerrainObject : public ACBP_AttackTerrainObject
{
	GENERATED_BODY()

public:
	ACBP_Normal_AttackTerrainObject();

	virtual void BeginPlay() override;
};
