// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/CBP_Skill.h"
#include "Skill\ProjectileType\CBP_SimpleProjectileSkill.h"
#include "CBP_Palatos_Skill.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API ACBP_Palatos_Skill : public ACBP_Skill
{
	GENERATED_BODY()
	
public:
	ACBP_Palatos_Skill();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	void Play(bool const InSuccess, bool& Success)override;
	void SetSpawn(AActor* centerActor)override;

	void SetStart()override;
	void SetEnd() override;

private:
	bool isPlay = false;

public:
	UPROPERTY(EditDefaultsOnly) int PalatosNum = 1;
	UPROPERTY(EditDefaultsOnly) float PalatosLenght = 100;

	UPROPERTY(EditDefaultsOnly) float DelayTime = 0;
	UPROPERTY(EditDefaultsOnly) float MoveSpeed = 3500;

	UPROPERTY(EditDefaultsOnly) float ChargeTime = 1;
	UPROPERTY(EditDefaultsOnly) bool isChargeType = true;

	UPROPERTY(EditDefaultsOnly) TSubclassOf<ACBP_SimpleProjectileSkill> attackSkillClass;
	UPROPERTY(EditDefaultsOnly) UAnimMontage* SetEndMontage;

protected:
	UPROPERTY() FVector PalatosVelocity;
	UPROPERTY() float PalatosMoveLenght = 1000;

	TArray<ACBP_Skill*> spawnPalatos;

	float curTime = 0;
	int count = 0;
};
