// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/Animaion/ACBP_AICharacter_Soldier_Gun.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/CBP_Character.h"

#include "Macro/KismetMacro.h"

#include "Logger/Logger.h"


UACBP_AICharacter_Soldier_Gun::UACBP_AICharacter_Soldier_Gun()
{

}

void UACBP_AICharacter_Soldier_Gun::NativeUpdateAnimation(float const DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (ACBP_Character* character = Cast<ACBP_Character>(TryGetPawnOwner()))
	{
		AActor* target = character->target;
		if (target == nullptr) { pitch = 0; return; }

		FVector shotLocation = character->GetActorLocation();
		FVector targetLocation = target->GetActorLocation();

		pitch = UKismetMathLibrary::FindLookAtRotation(shotLocation, targetLocation).Pitch;
	}
}

