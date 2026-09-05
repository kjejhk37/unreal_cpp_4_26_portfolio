// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBP_FootmanSkel_Attack.generated.h"

UCLASS()
class CPROJECT_API UCBP_FootmanSkel_Attack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UCBP_FootmanSkel_Attack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere) float targetAttackLenght = 300;
};
