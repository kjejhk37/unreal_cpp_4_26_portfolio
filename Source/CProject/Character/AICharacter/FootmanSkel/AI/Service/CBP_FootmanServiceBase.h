// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CBP_FootmanServiceBase.generated.h"

UCLASS()
class CPROJECT_API UCBP_FootmanServiceBase : public UBTService
{
	GENERATED_BODY()

public:
	UCBP_FootmanServiceBase();

	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	
};
