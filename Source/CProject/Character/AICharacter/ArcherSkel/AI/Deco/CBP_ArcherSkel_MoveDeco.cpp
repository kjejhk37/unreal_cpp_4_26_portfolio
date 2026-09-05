// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/ArcherSkel/AI/Deco/CBP_ArcherSkel_MoveDeco.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/CBP_AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UCBP_ArcherSkel_MoveDeco::UCBP_ArcherSkel_MoveDeco()
{

}

bool UCBP_ArcherSkel_MoveDeco::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
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

