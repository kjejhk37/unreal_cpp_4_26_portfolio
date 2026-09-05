// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "CBP_FootmanSkel_GuardDeco.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API UCBP_FootmanSkel_GuardDeco : public UBTDecorator
{
	GENERATED_BODY()

public:
	UCBP_FootmanSkel_GuardDeco();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	
};
