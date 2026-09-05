// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Animation/CABP_Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/CBP_Character.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Logger/Logger.h"

UCABP_Character::UCABP_Character()
{

}

void UCABP_Character::NativeUpdateAnimation(float const DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);


	//	if (AActor* const OwningActor = GetOwningActor())
	if (auto* const OwningActor = TryGetPawnOwner())
	{
		FVector const Velocity = OwningActor->GetVelocity();
		speed = Velocity.Size2D();

		FRotator Rotator = OwningActor->GetControlRotation();

		if (speed == 0)
		{
			isMove = false;

			
//			/*============================================= IK ==============================================*/
//			float DistanceL;
//			FRotator RotatorL;
//
//			float DistanceR;
//			FRotator RotatorR;
//
//			
//			int32 const max_Heigh_Difference = 15;
//
//			TraceForIK(IKBoneL, DistanceL, RotatorL);
//			TraceForIK(IKBoneR, DistanceR, RotatorR);
//
//			DistanceL = (DistanceL == TraceDistance) ? DistanceR - max_Heigh_Difference : DistanceL;
//			DistanceR = (DistanceR == TraceDistance) ? DistanceL - max_Heigh_Difference : DistanceR;
//
//			/* ==================================== Pelvis Add ======================================*/
//
//			float DistanceP = FMath::Min(DistanceL, DistanceR);
//			TranslationP.Z = FMath::FInterpTo(TranslationP.Z, DistanceP, DeltaSeconds, InterpSpeed);
//
//			/*======================================================================================*/
//			TranslationL.Z = FMath::FInterpTo(TranslationL.Z, DistanceL - DistanceP, DeltaSeconds, InterpSpeed);
//			TranslationR.Z = FMath::FInterpTo(TranslationR.Z, DistanceR - DistanceP, DeltaSeconds, InterpSpeed);
//
//			RotationL = FMath::RInterpTo(RotationL, RotatorL, DeltaSeconds, InterpSpeed);
//			RotationR = FMath::RInterpTo(RotationR, RotatorR, DeltaSeconds, InterpSpeed);

			
		}
		else
		{
			isMove = true;
		}

	}

	if (ACBP_Character* character = Cast<ACBP_Character>(TryGetPawnOwner()))
	{
		bool isDown = false;
		character->IsCharacterState(ECharacterState::Down, isDown);
	
		bool isCurFalling = character->GetCharacterMovement()->IsFalling();

		// 몇초뒤에 일어나는 건 나중에 더하는 걸루 하자(단순 귀찮)
		isDownFalling = (isDown && isCurFalling);

		isGuard = character->isGuard;

		isFalling = character->characterState == ECharacterState::Jump;

	}
}

void UCABP_Character::TraceForIK(FName const Bone, UPARAM(Ref) float& Distance, FRotator& Rotator)
{
	FVector const Target = GetOwningComponent()->GetSocketLocation(Bone);
	FVector const Root = GetOwningComponent()->GetSocketLocation(TEXT("Root"));
	FVector const Actor = GetOwningActor()->GetActorLocation();

	FVector const Start = { Target.X,Target.Y,Actor.Z };
	FVector const End = { Target.X,Target.Y,Root.Z - TraceDistance };

	FHitResult Result;

	UKismetSystemLibrary::LineTraceSingle(
		GetWorld(),
		Start,
		End,
		ETraceTypeQuery::TraceTypeQuery7,
		false,
		{ GetOwningActor() },
		EDrawDebugTrace::Type::ForOneFrame,
		Result,
		true
	);

	Distance = TraceDistance;
	Rotator = FRotator::ZeroRotator;

	if (Result.bBlockingHit == true)
	{
		Distance = Result.Location.Z - Root.Z;

		float const Roll = +UKismetMathLibrary::DegAtan2(Result.Normal.Y, Result.Normal.Z);
		float const Pitch = -UKismetMathLibrary::DegAtan2(Result.Normal.X, Result.Normal.Z);

		Rotator = { Pitch, 0, Roll };
	}

}