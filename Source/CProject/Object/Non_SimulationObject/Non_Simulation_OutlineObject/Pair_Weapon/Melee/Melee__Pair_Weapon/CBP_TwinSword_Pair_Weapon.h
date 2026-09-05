// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/Pair_Weapon/Melee/CBP_Melee_Pair_Weapon.h"
#include "CBP_TwinSword_Pair_Weapon.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API ACBP_TwinSword_Pair_Weapon : public ACBP_Melee_Pair_Weapon
{
	GENERATED_BODY()

public:
	ACBP_TwinSword_Pair_Weapon();
protected:
	void Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType) override;
	
};
