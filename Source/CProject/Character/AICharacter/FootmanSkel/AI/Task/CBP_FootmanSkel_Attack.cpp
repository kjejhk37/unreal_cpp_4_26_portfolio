// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/FootmanSkel/AI/Task/CBP_FootmanSkel_Attack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/CBP_AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

#include "Macro/KismetMacro.h"
#include "Logger/Logger.h"

UCBP_FootmanSkel_Attack::UCBP_FootmanSkel_Attack()
{

}

EBTNodeResult::Type UCBP_FootmanSkel_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACBP_AICharacter* character = Cast<ACBP_AICharacter>(OwnerComp.GetAIOwner()->GetPawn());
	AActor* target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("Target")));

	if(character == nullptr) return EBTNodeResult::Type::Failed;
	if (target == nullptr) return EBTNodeResult::Type::Failed;

	FVector velocity;
	float length;

	(target->GetActorLocation() - character->GetActorLocation()).ToDirectionAndLength(velocity, length);

	if (targetAttackLenght > length)
	{
		character->Skill(ESkillType::Skill_2, true);
	}


	return EBTNodeResult::Type::Succeeded;
}

void UCBP_FootmanSkel_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

}



