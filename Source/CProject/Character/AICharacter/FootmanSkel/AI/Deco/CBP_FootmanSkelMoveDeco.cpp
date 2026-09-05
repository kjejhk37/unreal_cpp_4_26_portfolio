// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/FootmanSkel/AI/Deco/CBP_FootmanSkelMoveDeco.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/CBP_AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

#include "Logger/Logger.h"

UCBP_FootmanSkelMoveDeco::UCBP_FootmanSkelMoveDeco()
{

}

bool UCBP_FootmanSkelMoveDeco::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	// Perform Condition Check AI
	ACBP_AICharacter* character = Cast<ACBP_AICharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (character == nullptr) return false;

	AActor* target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("Target")));
	if (target == nullptr) return false;

	bool canMove = false;
	character->CanMove(canMove);
	if (canMove == false)
	{
		character->GetController()->StopMovement();
		return false;
	}

	if (character->isGuard == true)
	{
		character->GetController()->StopMovement();
		return false;
	}


	return true;
}

