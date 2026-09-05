// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "CBP_FootmanSkelMoveDeco.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API UCBP_FootmanSkelMoveDeco : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UCBP_FootmanSkelMoveDeco();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};
