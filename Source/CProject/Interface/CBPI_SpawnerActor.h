// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CBPI_SpawnerActor.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCBPI_SpawnerActor : public UInterface
{
	GENERATED_BODY()
};


class CPROJECT_API ICBPI_SpawnerActor
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetSpawnerActor(AActor* InSpawnedActor)PURE_VIRTUAL(ICBPI_SpawnerActor::SetSpawnerActor, return;);
	virtual void SetDeleteSpawnedActor(AActor* InDeleteSpawnedActor)PURE_VIRTUAL(ICBPI_SpawnerActor::SetDeleteSpawnedActor, return;);

};
