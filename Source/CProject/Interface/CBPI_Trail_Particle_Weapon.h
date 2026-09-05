// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CBPI_Trail_Particle_Weapon.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCBPI_Trail_Particle_Weapon : public UInterface
{
	GENERATED_BODY()
};

class CPROJECT_API ICBPI_Trail_Particle_Weapon
{
	GENERATED_BODY()

public:
	virtual void TrailParticleActivate() PURE_VIRTUAL(ICBPI_Trail_Particle_Weapon::TrailParticleActivate, return;);
	virtual void TrailParticleDeActivate() PURE_VIRTUAL(ICBPI_Trail_Particle_Weapon::TrailParticleDeActivate, return;);


};
