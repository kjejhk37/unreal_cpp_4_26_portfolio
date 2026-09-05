// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "MyBTService.generated.h"


UCLASS()
class CPROJECT_API UMyBTService : public UBTService
{
	GENERATED_BODY()
	
public:
	UMyBTService();

	// 사용처 모르겠음
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	// 입력시
	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
public:
	UPROPERTY(EditAnywhere) FBlackboardKeySelector Target;
	UPROPERTY(EditAnywhere) FBlackboardKeySelector Location;
};
