// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/Spawn_Skill/CBP_Spawn_Skill.h"
#include "Character/AICharacter/CBP_AICharacter.h"
#include "CBP_SpawnSkelArmy_Skill.generated.h"

UCLASS()
class CPROJECT_API ACBP_SpawnSkelArmy_Skill : public ACBP_Spawn_Skill
{
	GENERATED_BODY()

public:
	ACBP_SpawnSkelArmy_Skill();
	void OnConstruction(const FTransform& Transform) override;
	//	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void Play(bool const InSuccess, bool& Success)override;
	void SetSpawn(AActor* centerActor) override;

public:
	UPROPERTY(EditDefaultsOnly) class UParticleSystem* SpawnParticle;

	UPROPERTY(BlueprintReadOnly, Category = "Set") TSubclassOf<ACBP_AICharacter> spawnCharacterClass;
	UPROPERTY(BlueprintReadOnly, Category = "Set") float startRotatorYaw;

	UPROPERTY(BlueprintReadOnly, Category = "Setting")  bool isSpawnLife = false;
	UPROPERTY(BlueprintReadOnly, Category = "Setting")  float spawnTime = 5;

};
