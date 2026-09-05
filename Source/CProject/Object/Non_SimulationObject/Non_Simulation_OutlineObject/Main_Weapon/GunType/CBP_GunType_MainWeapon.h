// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/Main_Weapon/CBP_MainWeapon.h"
#include "Interface/CBPI_GunWeapon.h"
#include "DataAsset/C_GunInfoDataAsset.h"
#include "Object/SimulationObject/Non_Interaction_Object/CBP_Non_InteractionObject.h"
#include "CBP_GunType_MainWeapon.generated.h"

UCLASS()
class CPROJECT_API ACBP_GunType_MainWeapon : public ACBP_MainWeapon ,public ICBPI_GunWeapon
{
	GENERATED_BODY()
public:
	ACBP_GunType_MainWeapon();

	virtual void ShotTrace(bool const InSuccess, bool& Success, FHitResult& OutHit, bool& IsHit)override;

	virtual void ReLoad(bool& Success)override;
	virtual void CanShot(bool& canShot, int Num)override;
	virtual void DecreasingBullet(bool& Success,int Num)override;

	virtual void SpawnFaiingBullet()override;
	virtual void SpawnFaiingMagazine()override;

	virtual void Shot(int ShotNum, UAnimMontage* shotMontage) override;

	void UpdateInterface(bool Equip) override;
public:
	bool CanSpeaker() {return speakerType;}

protected:
	void Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType) override;
	virtual void BeginPlay() override;

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Setting") UC_GunInfoDataAsset* GunInfoDataAsset;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Setting") UAnimMontage* ShotMontage;

	void SetGunInfo();

	TSubclassOf<ACBP_Non_InteractionObject> FallingBullet;
	TSubclassOf<ACBP_Non_InteractionObject> FallingMagazine;

	FName MagazineSocket;
	FName BulletSocket;
	FName ShotSocket;

	float AttackLength;
	int RemainBullet;
	int MaxBullet;


	bool speakerType = false;

private:
	UAnimMontage* ShotMontageTemp;

};
