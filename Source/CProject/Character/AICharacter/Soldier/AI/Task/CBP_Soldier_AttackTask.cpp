// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/Soldier/AI/Task/CBP_Soldier_AttackTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/CBP_AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

#include "Logger/Logger.h"

UCBP_Soldier_AttackTask::UCBP_Soldier_AttackTask()
{

}

EBTNodeResult::Type UCBP_Soldier_AttackTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACBP_AICharacter* character = Cast<ACBP_AICharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (character == nullptr) return EBTNodeResult::Type::Failed;

	character->Skill(ESkillType::Skill_1, true);

	return EBTNodeResult::Type::Succeeded;
}

void UCBP_Soldier_AttackTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

}
