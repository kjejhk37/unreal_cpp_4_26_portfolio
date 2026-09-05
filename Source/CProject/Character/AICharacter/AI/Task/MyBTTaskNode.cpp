// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/AI/Task/MyBTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/CBP_AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

#include "Logger/Logger.h"

UMyBTTaskNode::UMyBTTaskNode()
{

}

EBTNodeResult::Type UMyBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACBP_AICharacter* character = Cast<ACBP_AICharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (character == nullptr) return EBTNodeResult::Type::Failed;

	character->Skill(ESkillType::Skill_1, true);

	return EBTNodeResult::Type::Succeeded;
}

void UMyBTTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

}