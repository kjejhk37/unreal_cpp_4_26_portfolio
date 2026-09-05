// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/CBP_Skill.h"
#include "Particle/CBP_Particle.h"
#include "CBP_Attach_Skill.generated.h"

UCLASS()
class CPROJECT_API ACBP_Attach_Skill : public ACBP_Skill
{
	GENERATED_BODY()

public:
	ACBP_Attach_Skill();
	void OnConstruction(const FTransform& Transform) override;
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void Play(bool const InSuccess, bool& Success)override;
	void SetSpawn(AActor* centerActor)override;

	void Attack() override;

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Set") int attackCount = 5;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Set") float playTime = 10;


	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Set") float playDelayTime = 0.25f;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Set") float endPlayDelayTime = 0.25f;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Set") float attackCoolTime = 1;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Set") TSubclassOf<ACBP_Skill> AttackskillClass;

public:
	UFUNCTION(BlueprintCallable) void StartAttack();
	UFUNCTION(BlueprintCallable) void EndSkill();

protected:
	UPROPERTY(VisibleAnywhere) class UParticleSystemComponent* particle;

private:
	FTimerHandle Timer;

};
