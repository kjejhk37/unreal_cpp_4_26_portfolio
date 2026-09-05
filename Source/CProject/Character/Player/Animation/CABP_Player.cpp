// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/Animation/CABP_Player.h"
#include "Character/Player/CBP_Player.h"

#include "Macro/IncludeMacro.h"
#include "Macro/KismetMacro.h"

#include MainWeaponPath

#include "Logger/Logger.h"

UCABP_Player::UCABP_Player()
{

}

void UCABP_Player::NativeUpdateAnimation(float const DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	UpdateCharacterState();

	if (auto* const player = Cast<ACBP_Player>(TryGetPawnOwner()))
	{
		ACBP_MainWeapon* mainWeapon = Cast<ACBP_MainWeapon>(player->main_Weapon);
		if (mainWeapon == nullptr)
		{
			weaponName = EWeaponName::None;
			return;
		}

		weaponName = mainWeapon->weaponName;
	}

	UpdateAim();

}

void UCABP_Player::UpdateAim()
{
	ACBP_Player* player = Cast<ACBP_Player>(TryGetPawnOwner());
	if (player == nullptr) return;

	bool bUpdate = false;
	bool addPitchCorrection = false;
	switch (weaponName)
	{
	case EWeaponName::Bow:
		bUpdate = true;
		addPitchCorrection = true;
		break;
	case EWeaponName::Rifle:
		bUpdate = true;
		break;
	}

	if (bUpdate == false)
	{
		direction = 0;
		pitch = 0;
		return;
	}

	FRotator Rotator = player->GetControlRotation();
	Rotator = FRotator(0, Rotator.Yaw, 0);
	FVector velocity = player->GetVelocity();
	velocity.Z = 0;

	direction = CalculateDirection(velocity, Rotator);

	float arrowSpeed = 3500;

	FVector cameraForwardVector = UKismetMathLibrary::GetForwardVector(GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraRotation());
	FVector cameraLocation = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation();
	FVector end = cameraLocation + (cameraForwardVector * arrowSpeed);

	FHitResult result;

	UKismetSystemLibrary::LineTraceSingle(
		GetWorld(),
		cameraLocation,
		end,
		ETraceTypeQuery::TraceTypeQuery3,
		false,
		{ player },
		EDrawDebugTrace::Type::None,
		result,
		true
	);

	FVector playerLocation = player->GetActorLocation();
	FVector aimLocation = end;
	if (result.bBlockingHit)
	{
		aimLocation = result.Location;
	}


	float startPitch = UKismetMathLibrary::FindLookAtRotation(playerLocation, aimLocation).Pitch;

	if (addPitchCorrection == true)
	{
		float targetLenght = (playerLocation - aimLocation).Size();

		startPitch += 0.5f*UKismetMathLibrary::DegAsin((980 * targetLenght) / (arrowSpeed * arrowSpeed));
	}


	pitch = startPitch;
}

void UCABP_Player::UpdateCharacterState()
{
	// A 에서 B로 바뀌는 시점을 잡음
	if (auto* const player = Cast<ACBP_Player>(TryGetPawnOwner()))
	{
		if ((player->characterState == characterState)) return;

		ECharacterState newCharacterState = player->characterState;

		if (characterState != ECharacterState::Dodge && newCharacterState == ECharacterState::Dodge)
		{
			StartDodge();
		}

		if (characterState != ECharacterState::Jump && newCharacterState == ECharacterState::Jump)
		{
			StartJump();
		}

		if (characterState == ECharacterState::Jump && newCharacterState == ECharacterState::Idle)
		{
			EndJump();
		}

		characterState = player->characterState;

	}
}


void UCABP_Player::StartDodge()
{
	if (auto* const player = Cast<ACBP_Player>(TryGetPawnOwner()))
	{
		player->SetDodgeDirection();
	}
}

void UCABP_Player::StartJump()
{
	if (auto* const player = Cast<ACBP_Player>(TryGetPawnOwner()))
	{
//		player->JumpStart();
	}
}

void UCABP_Player::EndJump()
{
	if (auto* const player = Cast<ACBP_Player>(TryGetPawnOwner()))
	{
		player->JumpEnd();
	}
}

void UCABP_Player::SetZoom(bool InisZoom)
{
	isZoom = InisZoom;
}