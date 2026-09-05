// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/Soldier/AI/Deco/CBP_Soldier_AttackDeco.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/CBP_AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"


UCBP_Soldier_AttackDeco::UCBP_Soldier_AttackDeco()
{

}

bool UCBP_Soldier_AttackDeco::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	// Perform Condition Check AI
	
	bool result = true;

	ACBP_AICharacter* character = Cast<ACBP_AICharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (character == nullptr) result = false;

	AActor* target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("Target")));

	if (target == nullptr) result = false;

	bool canAction = false;
	character->CanActionSkill(ESkillType::Skill_1, canAction);
	if (canAction == false)  result = false;


	if (result == true)
	{
		character->GetController()->StopMovement();
	}

	return result;
}

