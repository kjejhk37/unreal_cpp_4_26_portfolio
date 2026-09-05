// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBP_Soldier_Move_Task.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API UCBP_Soldier_Move_Task : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UCBP_Soldier_Move_Task();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere) float lenght = 500;
};
