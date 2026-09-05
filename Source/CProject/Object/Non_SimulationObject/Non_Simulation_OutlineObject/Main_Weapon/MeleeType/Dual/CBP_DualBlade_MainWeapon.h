// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/Main_Weapon/MeleeType/CBP_Melee_MainWeapon.h"
#include "CBP_DualBlade_MainWeapon.generated.h"


UCLASS()
class CPROJECT_API ACBP_DualBlade_MainWeapon : public ACBP_Melee_MainWeapon
{
	GENERATED_BODY()

public:
	ACBP_DualBlade_MainWeapon();
	void OnConstruction(const FTransform& Transform) override;
protected:
	void Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType) override;
	virtual void BeginPlay() override;

public:
	void Activate(bool InSuccess, bool& OutSuccess) override;
	void DeActivate(bool InSuccess, bool& OutSuccess) override;

	void TrailParticleActivate() override;
	void TrailParticleDeActivate() override;

protected:
	UFUNCTION() void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
	
};
