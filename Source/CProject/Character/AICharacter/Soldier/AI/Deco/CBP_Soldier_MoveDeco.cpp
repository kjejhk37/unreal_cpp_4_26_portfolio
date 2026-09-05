// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/Soldier/AI/Deco/CBP_Soldier_MoveDeco.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/CBP_AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UCBP_Soldier_MoveDeco::UCBP_Soldier_MoveDeco()
{

}

bool UCBP_Soldier_MoveDeco::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	// Perform Condition Check AI
	ACBP_AICharacter* character = Cast<ACBP_AICharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (character == nullptr) return false;

	bool canMove = false;
	character->CanMove(canMove);
	if (canMove == false)
	{
		character->GetController()->StopMovement();
		return false;
	}


	return true;
}


