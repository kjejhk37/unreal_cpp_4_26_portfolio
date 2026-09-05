// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/FootmanSkel/AI/Deco/CBP_FootmanSkel_UnGuardDeco.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/CBP_AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UCBP_FootmanSkel_UnGuardDeco::UCBP_FootmanSkel_UnGuardDeco()
{

}

bool UCBP_FootmanSkel_UnGuardDeco::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	// Perform Condition Check AI
	ACBP_AICharacter* character = Cast<ACBP_AICharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (character == nullptr) return false;

	AActor* target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("Target")));

	if (target == nullptr) return true;
	
	FVector velocity;
	float length;

	(target->GetActorLocation() - character->GetActorLocation()).ToDirectionAndLength(velocity, length);

	if (targetLenght < length)
	{
		return true;
	}

	return false;
}




