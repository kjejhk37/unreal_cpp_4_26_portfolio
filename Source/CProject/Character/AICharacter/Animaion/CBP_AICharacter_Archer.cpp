// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/Animaion/CBP_AICharacter_Archer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/CBP_Character.h"

#include "Macro/KismetMacro.h"

#include "Logger/Logger.h"


UCBP_AICharacter_Archer::UCBP_AICharacter_Archer()
{

}

void UCBP_AICharacter_Archer::NativeUpdateAnimation(float const DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (ACBP_Character* character = Cast<ACBP_Character>(TryGetPawnOwner()))
	{
		AActor* target = character->target;
		if (target == nullptr) { pitch = 0; return; }

		FVector shotLocation = character->GetActorLocation();
		FVector targetLocation = target->GetActorLocation();

		float targetLenght = (shotLocation - targetLocation).Size();

		pitch = UKismetMathLibrary::FindLookAtRotation(shotLocation, targetLocation).Pitch;
		pitch += 0.5f*UKismetMathLibrary::DegAsin((980 * targetLenght) / (3500 * 3500));
	}
	
}
