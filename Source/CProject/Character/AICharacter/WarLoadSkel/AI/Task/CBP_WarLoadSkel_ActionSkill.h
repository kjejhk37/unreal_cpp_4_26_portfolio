// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Enums/EWeapon.h"
#include "CBP_WarLoadSkel_ActionSkill.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API UCBP_WarLoadSkel_ActionSkill : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UCBP_WarLoadSkel_ActionSkill();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere) float targetAttackLenght = 500;
	UPROPERTY(EditAnywhere) ESkillType skillType = ESkillType::None;
};
