// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CBPI_Bow.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCBPI_Bow : public UInterface
{
	GENERATED_BODY()
};

class CPROJECT_API ICBPI_Bow
{
	GENERATED_BODY()

public:
	virtual void SpawnArrow(bool& OutSuccess , AActor*& spawnArrowActor) PURE_VIRTUAL(ICBPI_Bow::SpawnArrow, return;);
	virtual void Shot(bool InSuccess,bool& OutSuccess) PURE_VIRTUAL(ICBPI_Bow::Shot, return;);

	virtual void PlayMontageCharging() PURE_VIRTUAL(ICBPI_Bow::PlayMontageCharging, return;);
	virtual void PlayMontageShoting() PURE_VIRTUAL(ICBPI_Bow::PlayMontageShoting, return;);


};
