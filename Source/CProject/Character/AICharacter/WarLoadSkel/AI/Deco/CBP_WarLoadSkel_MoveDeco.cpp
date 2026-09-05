// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/WarLoadSkel/AI/Deco/CBP_WarLoadSkel_MoveDeco.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/CBP_AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

#include "Logger/Logger.h"

UCBP_WarLoadSkel_MoveDeco::UCBP_WarLoadSkel_MoveDeco()
{

}

bool UCBP_WarLoadSkel_MoveDeco::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
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

	return true;
}



