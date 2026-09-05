// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/FootmanSkel/AI/Deco/CBP_FootmanSkel_GuardDeco.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/CBP_AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UCBP_FootmanSkel_GuardDeco::UCBP_FootmanSkel_GuardDeco()
{

}

bool UCBP_FootmanSkel_GuardDeco::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	// Perform Condition Check AI
	ACBP_AICharacter* character = Cast<ACBP_AICharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (character == nullptr) return false;

	AActor* target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("Target")));

	if (target == nullptr) return false;

	bool canAction = false;
	character->CanActionSkill(ESkillType::Skill_1, canAction);
	if (canAction == false)  return false;

	if (character->isGuard == true) return false;

	if (character->GuardGauge <= 500) return false;

	return true;
}



