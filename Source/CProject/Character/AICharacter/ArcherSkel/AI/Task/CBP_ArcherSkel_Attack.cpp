// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/ArcherSkel/AI/Task/CBP_ArcherSkel_Attack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/CBP_AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

#include "Macro/KismetMacro.h"
#include "Logger/Logger.h"

UCBP_ArcherSkel_Attack::UCBP_ArcherSkel_Attack()
{

}

EBTNodeResult::Type UCBP_ArcherSkel_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACBP_AICharacter* character = Cast<ACBP_AICharacter>(OwnerComp.GetAIOwner()->GetPawn());
	AActor* target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("Target")));

	character->Skill(ESkillType::Skill_1, true);

	if (character->characterState != ECharacterState::Skill) return EBTNodeResult::Type::Failed;
	
	return EBTNodeResult::Type::Succeeded;
}

void UCBP_ArcherSkel_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

}

