// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/Spawn_Skill/CBP_Spawn_Skill.h"
#include "Skill/Spawn_Skill/Simple/Homing/CBP_Spawn_HomingSkill.h"
#include "CBP_ArrowShower_Arrow_Spawn.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API ACBP_ArrowShower_Arrow_Spawn : public ACBP_Spawn_Skill
{
	GENERATED_BODY()
	
public:
	ACBP_ArrowShower_Arrow_Spawn();
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
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Setting") float DelayTime = 1;

	UFUNCTION() void Attack();
	UFUNCTION() void EndSkill();

	FVector AttackScale = FVector(1, 1, 1);

protected:
	UPROPERTY(VisibleAnywhere) class UParticleSystemComponent* particle;

	UPROPERTY(EditDefaultsOnly) TSubclassOf<ACBP_Spawn_HomingSkill> skillClass;
	ACBP_Skill* temp;

	bool isSkillStart = false;
};
