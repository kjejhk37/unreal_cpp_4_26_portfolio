// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "MyBTDecorator.generated.h"

UCLASS()
class CPROJECT_API UMyBTDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
	UMyBTDecorator();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	
};
