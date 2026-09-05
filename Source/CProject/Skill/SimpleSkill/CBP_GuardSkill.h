// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/CBP_Skill.h"
#include "CBP_GuardSkill.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API ACBP_GuardSkill : public ACBP_Skill
{
	GENERATED_BODY()

public:
	ACBP_GuardSkill();

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
};
