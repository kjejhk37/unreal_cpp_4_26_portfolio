// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/AI/Task/CBP_CharacterMoveToStop.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/CBP_AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

#include "Logger/Logger.h"

UCBP_CharacterMoveToStop::UCBP_CharacterMoveToStop()
{

}

EBTNodeResult::Type UCBP_CharacterMoveToStop::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACBP_AICharacter* character = Cast<ACBP_AICharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (character == nullptr) return EBTNodeResult::Type::Failed;

	character->GetController()->StopMovement();

	return EBTNodeResult::Type::Succeeded;
}

void UCBP_CharacterMoveToStop::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

}
