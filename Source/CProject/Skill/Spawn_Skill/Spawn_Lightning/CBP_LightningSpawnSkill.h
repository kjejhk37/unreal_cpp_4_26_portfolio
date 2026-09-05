// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/Spawn_Skill/CBP_Spawn_Skill.h"
#include "Particle/CBP_Particle.h"
#include "CBP_LightningSpawnSkill.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API ACBP_LightningSpawnSkill : public ACBP_Spawn_Skill
{
	GENERATED_BODY()

public:
	ACBP_LightningSpawnSkill();
	void OnConstruction(const FTransform& Transform) override;
	//	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void Play(bool const InSuccess, bool& Success)override;
	void SetSpawn(AActor* centerActor) override;

	void SetStart()override;
	void SetEnd() override;

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Setting") float DelayTime = 2;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Setting") float particlePlayTime = 1.5f;

	UFUNCTION() void Attack();
	UFUNCTION() void EndSkill();
protected:
	UPROPERTY(VisibleAnywhere) class UParticleSystemComponent* particle;
	UPROPERTY(VisibleAnywhere) class UParticleSystemComponent* LightingParticle;

	UPROPERTY(EditDefaultsOnly) TSubclassOf<ACBP_Particle> attackParticleActorClass;


};
