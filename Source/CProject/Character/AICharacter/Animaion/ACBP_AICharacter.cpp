// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/Animaion/ACBP_AICharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/CBP_Character.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Logger/Logger.h"

UACBP_AICharacter::UACBP_AICharacter()
{

}

void UACBP_AICharacter::NativeUpdateAnimation(float const DeltaSeconds)
{
//	Super::NativeUpdateAnimation(DeltaSeconds);

	//	if (AActor* const OwningActor = GetOwningActor())
	if (auto* const OwningActor = TryGetPawnOwner())
	{
		//		speed = OwningActor->GetVelocity().Size2D();
		FVector const Velocity = OwningActor->GetVelocity();

		speed = Velocity.Size2D();

//		FRotator Rotator = OwningActor->GetControlRotation();
		//		direction = CalculateDirection(Velocity, Rotator);

	}

	if (ACBP_Character* character = Cast<ACBP_Character>(TryGetPawnOwner()))
	{
		bool isDown = false;
		character->IsCharacterState(ECharacterState::Down, isDown);

		bool isCurFalling = character->GetCharacterMovement()->IsFalling();

		// 몇초뒤에 일어나는 건 나중에 더하는 걸루 하자(단순 귀찮)
		isDownFalling = (isDown && isCurFalling);

		isGuard = character->isGuard;
	}
}

void UACBP_AICharacter::SetEndSpawn()
{
	EndSpawn = true;
}
