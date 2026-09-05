// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CBP_ArcherSkel_ServiceBase.generated.h"

UCLASS()
class CPROJECT_API UCBP_ArcherSkel_ServiceBase : public UBTService
{
	GENERATED_BODY()

public:
	UCBP_ArcherSkel_ServiceBase();

	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
public:
//	UPROPERTY(EditAnywhere) FBlackboardKeySelector Target;
};
