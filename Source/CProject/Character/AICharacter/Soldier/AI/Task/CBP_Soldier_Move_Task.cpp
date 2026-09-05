// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/Soldier/AI/Task/CBP_Soldier_Move_Task.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/CBP_AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

#include "Macro/MathMacro.h"
#include "Macro/KismetMacro.h"

#include "Logger/Logger.h"

UCBP_Soldier_Move_Task::UCBP_Soldier_Move_Task()
{

}

EBTNodeResult::Type UCBP_Soldier_Move_Task::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACBP_AICharacter* character = Cast<ACBP_AICharacter>(OwnerComp.GetAIOwner()->GetPawn());
	AActor* target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("Target")));


	FVector targetLocation;
	bool isSpawn = false;

	if (target != nullptr)
		targetLocation = target->GetActorLocation();
	else
	{
		if (character->isSpawnAICharacter == true && character->GetInstigator() != nullptr)
		{
			targetLocation = ActorLocalToWorldLocation(character->SpawnerActor, character->spawnLocalLocation);
			isSpawn = true;
		}
		else
		{
			targetLocation = character->GetActorLocation();
		}
	}


	EPathFollowingRequestResult::Type returnValue;
	returnValue = Cast<AAIController>(character->GetController())->MoveToLocation(targetLocation, lenght, true, true, false, true, nullptr, true);
//	returnValue = Cast<AAIController>(character->GetController())->MoveToActor(target, lenght, true, true, true);
	
// RotationºÎºÐ
	FRotator newRotator = UKismetMathLibrary::FindLookAtRotation(character->GetActorLocation(), targetLocation);
	newRotator.Pitch = 0;
	newRotator.Roll = 0;

	character->SetActorRotation(newRotator);

	float tempLenght = lenght;

	if (isSpawn == true)
		tempLenght = -100;

	if ((character->GetActorLocation() - targetLocation).Size() >= tempLenght + 100)
	{
		return EBTNodeResult::Type::Failed;
	}

	return EBTNodeResult::Type::Succeeded;
}

void UCBP_Soldier_Move_Task::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

}


