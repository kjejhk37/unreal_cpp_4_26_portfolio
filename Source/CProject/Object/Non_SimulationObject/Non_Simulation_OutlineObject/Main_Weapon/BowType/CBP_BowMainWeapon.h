// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/Main_Weapon/CBP_MainWeapon.h"
#include "Interface/CBPI_Bow.h"
#include "CBP_BowMainWeapon.generated.h"

UCLASS()
class CPROJECT_API ACBP_BowMainWeapon : public ACBP_MainWeapon , public ICBPI_Bow
{
	GENERATED_BODY()
	
public:
	ACBP_BowMainWeapon();

	virtual void BeginPlay() override;

	void PlayMontageCharging()override;
	void PlayMontageShoting()override;

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Montage") UAnimMontage* ChargingMontage;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Montage") UAnimMontage* ShotingMontage;

	UFUNCTION() void BowOnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

/*
	void OnConstruction(const FTransform& Transform) override;
protected:
	void Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType) override;

	virtual void Tick(float DeltaTime) override;
public:
	void Activate(bool InSuccess, bool& OutSuccess) override;
	void DeActivate(bool InSuccess, bool& OutSuccess) override;

	void SpawnArrow(bool& OutSuccess, AActor*& spawnArrowActor)override;
	void Shot(bool InSuccess, bool& OutSuccess)override;

protected:
*/

};
