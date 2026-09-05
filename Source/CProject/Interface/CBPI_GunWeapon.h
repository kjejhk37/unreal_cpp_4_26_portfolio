// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CBPI_GunWeapon.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCBPI_GunWeapon : public UInterface
{
	GENERATED_BODY()
};

class CPROJECT_API ICBPI_GunWeapon
{
	GENERATED_BODY()

public:
	virtual void ShotTrace(bool const InSuccess,bool& Success,FHitResult& OutHit,bool& IsHit)PURE_VIRTUAL(ICBPI_GunWeapon::ShotTrace, return;);

	virtual void ReLoad(bool& Success)PURE_VIRTUAL(ICBPI_GunWeapon::ReLoad, return;);
	virtual void CanShot(bool& canShot, int Num)PURE_VIRTUAL(ICBPI_GunWeapon::CanShot, return;);
	virtual void DecreasingBullet(bool& Success, int Num) PURE_VIRTUAL(ICBPI_GunWeapon::DecreasingBullet, return;);


	virtual void SpawnFaiingBullet()PURE_VIRTUAL(ICBPI_GunWeapon::SpawnFaiingBullet, return;);
	virtual void SpawnFaiingMagazine()PURE_VIRTUAL(ICBPI_GunWeapon::SpawnFaiingMagazine, return;);
};
