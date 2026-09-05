// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/NS_InteractionObject/Animation_Object/CBP_AnimationObject.h"
#include "CBP_ParkourAnimationObject.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API ACBP_ParkourAnimationObject : public ACBP_AnimationObject
{
	GENERATED_BODY()
		
public:
	ACBP_ParkourAnimationObject();
	virtual void BeginPlay() override;
};
