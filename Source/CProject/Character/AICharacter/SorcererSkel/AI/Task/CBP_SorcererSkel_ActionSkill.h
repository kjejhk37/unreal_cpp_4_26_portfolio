// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Enums/EWeapon.h"
#include "CBP_SorcererSkel_ActionSkill.generated.h"


UCLASS()
class CPROJECT_API UCBP_SorcererSkel_ActionSkill : public UBTTaskNode
{
	GENERATED_BODY()


public:
	UCBP_SorcererSkel_ActionSkill();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere) float targetAttackLenght = 1000;
	UPROPERTY(EditAnywhere) ESkillType skillType = ESkillType::None;

};
