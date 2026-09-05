// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/SorcererSkel/AI/Task/CBP_SorcererSkel_ActionSkill.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/CBP_AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

#include "Macro/KismetMacro.h"
#include "Logger/Logger.h"

UCBP_SorcererSkel_ActionSkill::UCBP_SorcererSkel_ActionSkill()
{

}

EBTNodeResult::Type UCBP_SorcererSkel_ActionSkill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACBP_AICharacter* character = Cast<ACBP_AICharacter>(OwnerComp.GetAIOwner()->GetPawn());
	AActor* target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("Target")));

	if (character == nullptr) return EBTNodeResult::Type::Failed;
	if (target == nullptr) return EBTNodeResult::Type::Failed;

	FVector velocity;
	float length;

	(target->GetActorLocation() - character->GetActorLocation()).ToDirectionAndLength(velocity, length);

	if (targetAttackLenght > length)
	{
		character->Skill(skillType, true);
	}

	if(character->characterState != ECharacterState::Skill)
		return EBTNodeResult::Type::Failed;

	return EBTNodeResult::Type::Succeeded;
}

void UCBP_SorcererSkel_ActionSkill::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

}



