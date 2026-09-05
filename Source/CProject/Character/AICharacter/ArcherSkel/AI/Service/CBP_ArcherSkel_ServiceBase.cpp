// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/ArcherSkel/AI/Service/CBP_ArcherSkel_ServiceBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/CBP_AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

#include "Logger/Logger.h"

UCBP_ArcherSkel_ServiceBase::UCBP_ArcherSkel_ServiceBase()
{

}


void UCBP_ArcherSkel_ServiceBase::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	// ют╥б╫ц
	Super::OnSearchStart(SearchData);

	ACBP_AICharacter* character = Cast<ACBP_AICharacter>(SearchData.OwnerComp.GetAIOwner()->GetPawn());
	if (character == nullptr) return;

	SearchData.OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("Target"), character->target);
}

void UCBP_ArcherSkel_ServiceBase::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

}
