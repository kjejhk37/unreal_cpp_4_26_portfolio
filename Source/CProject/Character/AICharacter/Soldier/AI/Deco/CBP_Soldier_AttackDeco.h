// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "CBP_Soldier_AttackDeco.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API UCBP_Soldier_AttackDeco : public UBTDecorator
{
	GENERATED_BODY()

public:
	UCBP_Soldier_AttackDeco();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;


	
};
