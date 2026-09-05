// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/Main_Weapon/MagicType/CBP_MagicWeapon.h"
#include "CBP_SorcererSkel_MainWeapon.generated.h"


UCLASS()
class CPROJECT_API ACBP_SorcererSkel_MainWeapon : public ACBP_MagicWeapon
{
	GENERATED_BODY()
	
public:
	ACBP_SorcererSkel_MainWeapon();

	virtual void BeginPlay() override;
};
