// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "CBP_WarLoadSkel_MoveDeco.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API UCBP_WarLoadSkel_MoveDeco : public UBTDecorator
{
	GENERATED_BODY()


public:
	UCBP_WarLoadSkel_MoveDeco();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	
};
