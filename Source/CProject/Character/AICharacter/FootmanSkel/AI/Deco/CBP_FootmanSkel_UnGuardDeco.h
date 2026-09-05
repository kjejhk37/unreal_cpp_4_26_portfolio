// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "CBP_FootmanSkel_UnGuardDeco.generated.h"


UCLASS()
class CPROJECT_API UCBP_FootmanSkel_UnGuardDeco : public UBTDecorator
{
	GENERATED_BODY()

public:
	UCBP_FootmanSkel_UnGuardDeco();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere) float targetLenght = 500;

};
