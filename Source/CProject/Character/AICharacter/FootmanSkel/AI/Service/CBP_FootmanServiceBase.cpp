// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/FootmanSkel/AI/Service/CBP_FootmanServiceBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/CBP_AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

#include "Logger/Logger.h"

UCBP_FootmanServiceBase::UCBP_FootmanServiceBase()
{

}


void UCBP_FootmanServiceBase::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	// ют╥б╫ц
	Super::OnSearchStart(SearchData);

	ACBP_AICharacter* character = Cast<ACBP_AICharacter>(SearchData.OwnerComp.GetAIOwner()->GetPawn());
	if (character == nullptr) return;

	SearchData.OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("Target"), character->target);
}

void UCBP_FootmanServiceBase::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

}

