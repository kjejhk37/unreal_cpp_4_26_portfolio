// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/AI/Task/CBP_Character_RotationToTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/CBP_AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

#include "Macro/KismetMacro.h"

#include "Logger/Logger.h"

UCBP_Character_RotationToTarget::UCBP_Character_RotationToTarget()
{

}

EBTNodeResult::Type UCBP_Character_RotationToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACBP_AICharacter* character = Cast<ACBP_AICharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if(character == nullptr) return EBTNodeResult::Type::Failed;
	AActor* target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("Target")));
	if(target == nullptr) return EBTNodeResult::Type::Failed;

	FRotator newRotator = UKismetMathLibrary::FindLookAtRotation(character->GetActorLocation(), target->GetActorLocation());
	newRotator.Pitch = 0;
	newRotator.Roll = 0;

	character->SetActorRotation(newRotator);

	return EBTNodeResult::Type::Succeeded;
}

void UCBP_Character_RotationToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

}


