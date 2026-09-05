// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/AI/Deco/CBP_CharacterDeadDeco.h"
#include "Character/CBP_Character.h"
#include "AIController.h"

UCBP_CharacterDeadDeco::UCBP_CharacterDeadDeco()
{

}

bool UCBP_CharacterDeadDeco::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	// Perform Condition Check AI
	ACBP_Character* character = Cast<ACBP_Character>(OwnerComp.GetAIOwner()->GetPawn());
	if (character == nullptr) return false;
	if (character->characterState == ECharacterState::Dead) return false;
	
	if (character->curHp <= 0) return false;

	return true;
}

