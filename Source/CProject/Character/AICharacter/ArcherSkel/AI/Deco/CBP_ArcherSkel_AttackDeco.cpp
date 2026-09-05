// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/ArcherSkel/AI/Deco/CBP_ArcherSkel_AttackDeco.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/CBP_AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UCBP_ArcherSkel_AttackDeco::UCBP_ArcherSkel_AttackDeco()
{

}

bool UCBP_ArcherSkel_AttackDeco::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	// Perform Condition Check AI
	ACBP_AICharacter* character = Cast<ACBP_AICharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (character == nullptr) return false;

	AActor* target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("Target")));

	if (target == nullptr) return false;

	bool canAction = false;
	character->CanActionSkill(ESkillType::Skill_1, canAction);
	if (canAction == false)  return false;



	return true;
}


