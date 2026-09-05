// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SimpleAttackSkill/CBP_SimpleAttackSkill.h"
#include "CBP_Ring_SimpleAttackSkill.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API ACBP_Ring_SimpleAttackSkill : public ACBP_SimpleAttackSkill
{
	GENERATED_BODY()

public:
	ACBP_Ring_SimpleAttackSkill();

	void CorrectComponentSerch(bool& canAttack, AActor* OtherActor)override;

	UPROPERTY(EditDefaultsOnly, Category = "Set") float upDistance = 20;

	
	
};
