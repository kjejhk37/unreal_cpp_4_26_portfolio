// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/ArcherSkel/AI/Task/CBP_ArcherSkel_MoveToTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/CBP_AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

#include "Macro/KismetMacro.h"

#include "Logger/Logger.h"

UCBP_ArcherSkel_MoveToTarget::UCBP_ArcherSkel_MoveToTarget()
{

}

EBTNodeResult::Type UCBP_ArcherSkel_MoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACBP_AICharacter* character = Cast<ACBP_AICharacter>(OwnerComp.GetAIOwner()->GetPawn());
	AActor* target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("Target")));
	
	EPathFollowingRequestResult::Type returnValue;
	returnValue = Cast<AAIController>(character->GetController())->MoveToActor(target, 5000, true, true, true);
//	returnValue = Cast<AAIController>(character->GetController())->MoveToLocation(target->GetActorLocation(), 500, true, true, false, true, nullptr, true);

	FVector characterLocation = character->GetActorLocation();
	FVector targetLocation = target->GetActorLocation();

	FRotator newCharacterRotator = UKismetMathLibrary::FindLookAtRotation(characterLocation, targetLocation);
	newCharacterRotator.Pitch = 0;
	newCharacterRotator.Roll = 0;
	character->SetActorRotation(newCharacterRotator);

	if ((characterLocation - targetLocation).Size() < 5000)
	{
		character->GetController()->StopMovement();
		return EBTNodeResult::Type::Succeeded;
	}

	if(returnValue == EPathFollowingRequestResult::Failed) return EBTNodeResult::Type::Failed;
	if (returnValue == EPathFollowingRequestResult::RequestSuccessful) return EBTNodeResult::Type::Failed;

	return EBTNodeResult::Type::Succeeded;
}

void UCBP_ArcherSkel_MoveToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

}
