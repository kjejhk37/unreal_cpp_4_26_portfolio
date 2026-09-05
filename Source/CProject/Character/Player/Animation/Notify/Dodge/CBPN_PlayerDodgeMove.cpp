// Fill out your copyright notice in the Description page of Project Settings.


#include "CBPN_PlayerDodgeMove.h"
#include "Character/CBP_Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Macro/IncludeMacro.h"
#include "Macro/KismetMacro.h"

#include MainWeaponPath

#include "Logger/Logger.h"

UCBPN_PlayerDodgeMove::UCBPN_PlayerDodgeMove()
{

}

FString UCBPN_PlayerDodgeMove::GetNotifyName_Implementation() const
{
	return FString("Player_Dodge_Move");
}

void UCBPN_PlayerDodgeMove::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

}

void UCBPN_PlayerDodgeMove::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	ACBP_Character* character = Cast<ACBP_Character>(MeshComp->GetOwner());
	if (character == nullptr) return;

	ACBP_MainWeapon* curMainWeapon = Cast<ACBP_MainWeapon>(character->main_Weapon);
	if (curMainWeapon == nullptr)
	{
		character->GetCharacterMovement()->bOrientRotationToMovement = true;
		return;
	}

	EWeaponName weaponName = curMainWeapon->weaponName;
	bool bSetOrient = true;

	switch (weaponName)
	{
	case EWeaponName::Bow:
	case EWeaponName::Rifle:
		bSetOrient = false;
		break;
	}

	character->GetCharacterMovement()->bOrientRotationToMovement = bSetOrient;
}

void UCBPN_PlayerDodgeMove::NotifyTick(class USkeletalMeshComponent * MeshComp, class UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	if (ACBP_Character* character = Cast<ACBP_Character>(MeshComp->GetOwner()))
	{
		FHitResult result;

		FVector curCharacterRootLocation = character->GetMesh()->GetSocketLocation(FName("Root"));

		UKismetSystemLibrary::LineTraceSingle(
			character->GetWorld(),
			character->GetActorLocation(),
			character->GetActorLocation() + FVector(0, 0, -500),
			ETraceTypeQuery::TraceTypeQuery7,
			false,
			{},
			EDrawDebugTrace::Type::None,
			result,
			true
		);

		if (result.bBlockingHit == true)
		{
			curCharacterRootLocation = result.Location;
		}

		FVector forwardVector = character->GetMesh()->GetRightVector() * 2400.0f;
		FVector nextLocation = character->GetActorLocation() + forwardVector * FrameDeltaTime;

		UKismetSystemLibrary::LineTraceSingle(
			character->GetWorld(),
			nextLocation,
			nextLocation + FVector(0, 0, -500),
			ETraceTypeQuery::TraceTypeQuery7,
			false,
			{},
			EDrawDebugTrace::Type::None,
			result,
			true
		);


		if (result.bBlockingHit == true)
		{
			float lenght;
			FVector valocity;
			(result.Location - curCharacterRootLocation).ToDirectionAndLength(valocity, lenght);

			character->AddActorWorldOffset(valocity * lenght, true);
//			Logger::Print(valocity * lenght);
			
		}

		
		
/*
		FVector forwardVector = character->GetMesh()->GetRightVector() * 2400.0f;

		FHitResult result;

		UKismetSystemLibrary::LineTraceSingle(
			character->GetWorld(),
			character->GetActorLocation(),
			character->GetActorLocation() + FVector(0, 0, -500),
			ETraceTypeQuery::TraceTypeQuery7,
			false,
			{},
			EDrawDebugTrace::Type::None,
			result,
			true
		);

		if (result.bBlockingHit == true)
		{
			FRotator rotation = UKismetMathLibrary::MakeRotFromZ(result.Normal);
//			float const Roll = +UKismetMathLibrary::DegAtan2(result.Normal.Y, result.Normal.Z);
//			FRotator rotation(Roll, 0, 0);
			rotation.Yaw = 0;
			rotation.Pitch = 0;

			if (rotation.Roll < 45)
			{
				FMatrix rMatrix = FRotationMatrix::Make(FQuat(rotation));
				forwardVector = rMatrix.TransformPosition(forwardVector);
				forwardVector.Z = fabsf(forwardVector.Z);
			}

		}

		FVector nextLocation = character->GetActorLocation() + forwardVector * FrameDeltaTime;

		UKismetSystemLibrary::LineTraceSingle(
			character->GetWorld(),
			nextLocation,
			nextLocation + FVector(0, 0, -500),
			ETraceTypeQuery::TraceTypeQuery7,
			false,
			{},
			EDrawDebugTrace::Type::None,
			result,
			true
		);

		if(result.bBlockingHit == true)
			character->AddActorWorldOffset(forwardVector * FrameDeltaTime, true);

		*/
	}
}