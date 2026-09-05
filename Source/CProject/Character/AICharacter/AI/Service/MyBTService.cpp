// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/AI/Service/MyBTService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/CBP_AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

#include "Logger/Logger.h"

UMyBTService::UMyBTService()
{

}

void UMyBTService::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// 사용처 모르겠음

}

void UMyBTService::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	// 입력시
	Super::OnSearchStart(SearchData);

	ACBP_AICharacter* character = Cast<ACBP_AICharacter>(SearchData.OwnerComp.GetAIOwner()->GetPawn());
	if (character == nullptr) return;

	if (character->target == nullptr) return;

	SearchData.OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("Target"), character->target);
	SearchData.OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("Location"), character->target->GetActorLocation());


	UObject* temp;
	temp = SearchData.OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("Target"));
	Logger::Print(temp, 0, 1);

	
//	SetValueAsVector()
}

void UMyBTService::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// 사용처 모르겠음
}

void UMyBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

}