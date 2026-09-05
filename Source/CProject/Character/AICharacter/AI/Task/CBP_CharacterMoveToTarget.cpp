// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/AI/Task/CBP_CharacterMoveToTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/CBP_AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

#include "Logger/Logger.h"

UCBP_CharacterMoveToTarget::UCBP_CharacterMoveToTarget()
{

}

EBTNodeResult::Type UCBP_CharacterMoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACBP_AICharacter* character = Cast<ACBP_AICharacter>(OwnerComp.GetAIOwner()->GetPawn());
	AActor* target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("Target")));

	EPathFollowingRequestResult::Type returnValue;
	returnValue = Cast<AAIController>(character->GetController())->MoveToActor(target, lenght, true, true, true);
	//	returnValue = Cast<AAIController>(character->GetController())->MoveToLocation(target->GetActorLocation(), 500, true, true, false, true, nullptr, true);

	if ((character->GetActorLocation() - target->GetActorLocation()).Size() >= lenght + 100)
	{
		return EBTNodeResult::Type::Failed;
	}

	return EBTNodeResult::Type::Succeeded;
}

void UCBP_CharacterMoveToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

}

