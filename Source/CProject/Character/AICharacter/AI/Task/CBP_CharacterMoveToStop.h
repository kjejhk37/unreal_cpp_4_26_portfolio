// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBP_CharacterMoveToStop.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API UCBP_CharacterMoveToStop : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UCBP_CharacterMoveToStop();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
