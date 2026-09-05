// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CBPI_Weapon.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCBPI_Weapon : public UInterface
{
	GENERATED_BODY()
};

class CPROJECT_API ICBPI_Weapon
{
	GENERATED_BODY()

public:
	virtual void Activate(bool InSuccess , bool& OutSuccess) PURE_VIRTUAL(ICBPI_Weapon::Activate, return;);
	virtual void DeActivate(bool InSuccess, bool& OutSuccess) PURE_VIRTUAL(ICBPI_Weapon::DeActivate, return;);

	virtual void Shot(int ShotNum ,UAnimMontage* shotMontage) PURE_VIRTUAL(ICBPI_Weapon::Shot, return;);

	virtual void UpdateInterface(bool Equip) PURE_VIRTUAL(ICBPI_Weapon::UpdateInterface, return;);


};
