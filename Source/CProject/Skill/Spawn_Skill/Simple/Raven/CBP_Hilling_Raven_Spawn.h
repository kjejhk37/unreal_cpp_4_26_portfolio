// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/Spawn_Skill/Simple/Raven/CBP_Raven_Spawn.h"
#include "CBP_Hilling_Raven_Spawn.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API ACBP_Hilling_Raven_Spawn : public ACBP_Raven_Spawn
{
	GENERATED_BODY()

public:
	ACBP_Hilling_Raven_Spawn();

	void Attack() override;

protected:
	UPROPERTY(EditDefaultsOnly) class UParticleSystem* attackParticle;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<ACBP_Particle> attackParticleActorClass;

};
