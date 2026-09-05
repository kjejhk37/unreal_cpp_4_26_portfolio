// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/Main_Weapon/CBP_MainWeapon.h"
#include "Interface/CBPI_Trail_Particle_Weapon.h"
#include "CBP_MagicWeapon.generated.h"


UCLASS()
class CPROJECT_API ACBP_MagicWeapon : public ACBP_MainWeapon, public ICBPI_Trail_Particle_Weapon
{
	GENERATED_BODY()

public:
	ACBP_MagicWeapon();
	void OnConstruction(const FTransform& Transform) override;
protected:
	void Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType) override;
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	void Activate(bool InSuccess, bool& OutSuccess) override;
	void DeActivate(bool InSuccess, bool& OutSuccess) override;

	void TrailParticleActivate() override;
	void TrailParticleDeActivate() override;

protected:
	UPROPERTY(VisibleAnywhere) UParticleSystemComponent* particleSystem;
	
};
