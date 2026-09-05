// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "Enums/EWeapon.h"
#include "CBP_WarLoadSkel_ActionSkillDeco.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API UCBP_WarLoadSkel_ActionSkillDeco : public UBTDecorator
{
	GENERATED_BODY()

public:
	UCBP_WarLoadSkel_ActionSkillDeco();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere) ESkillType skillType = ESkillType::Skill_1;
	
};
