// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "Enums/EWeapon.h"
#include "CBP_SorcererSkel_SkillActionDeco.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API UCBP_SorcererSkel_SkillActionDeco : public UBTDecorator
{
	GENERATED_BODY()
public:
	UCBP_SorcererSkel_SkillActionDeco();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere) ESkillType skillType = ESkillType::Skill_1;

};
