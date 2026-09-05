// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/FootmanSkel/AI/Task/CBP_FootmanSkel_GuardTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/CBP_AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

#include "Macro/KismetMacro.h"
#include "Logger/Logger.h"

UCBP_FootmanSkel_GuardTask::UCBP_FootmanSkel_GuardTask()
{

}

EBTNodeResult::Type UCBP_FootmanSkel_GuardTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACBP_AICharacter* character = Cast<ACBP_AICharacter>(OwnerComp.GetAIOwner()->GetPawn());
	AActor* target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("Target")));

	character->Skill(ESkillType::Skill_1, true);

	if (character->isGuard == false) return EBTNodeResult::Type::Failed;

	FVector characterLocation = character->GetActorLocation();
	FVector targetLocation = target->GetActorLocation();

	FRotator newCharacterRotator = UKismetMathLibrary::FindLookAtRotation(characterLocation, targetLocation);
	character->SetActorRotation(newCharacterRotator);

	return EBTNodeResult::Type::Succeeded;
}

void UCBP_FootmanSkel_GuardTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

}


