// Fill out your copyright notice in the Description page of Project Settings.


#include "CBP_SimpleProjectileSkill.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Character/CBP_Character.h"

#include "Kismet/KismetMathLibrary.h"

#include "Macro/MyMacro.h"
#include "Macro/MathMacro.h"

#include "Logger/Logger.h"

ACBP_SimpleProjectileSkill::ACBP_SimpleProjectileSkill()
{
	CreateDefaultSubobjectAuto(Particle);
	CreateDefaultSubobjectAuto(Arrow);
	CreateDefaultSubobjectAuto(Projectile);

	Particle->SetupAttachment(center);
	Arrow->SetupAttachment(center);

	Projectile->ProjectileGravityScale = 0.0f;
}

void ACBP_SimpleProjectileSkill::BeginPlay()
{
	Super::BeginPlay();
}

void ACBP_SimpleProjectileSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!isPlay) return;

	curPlayTime += DeltaTime;

	if (isDelay)
	{
		if ((curPlayTime >= delayTime))
		{
			SetStart();

			curPlayTime = 0;
			SetVelocity();
			isDelay = false;
		}
		return;
	}

	if (curPlayTime >= playTime)
	{
		SetEnd();

		DestroyActor(mesh);
		DestroyActor(this);
	}

}

void ACBP_SimpleProjectileSkill::Play(bool const InSuccess, bool& Success)
{
	Super::Play(InSuccess, Success);

	Projectile->InitialSpeed = moveSpeed;
	Projectile->MaxSpeed = moveSpeed;

	bool succees;
	ThisClass::SetPointersToWorldPos(nullptr,succees);

	if (succees == false)
	{
		Success = false;
		return;
	}

	SpawnMeshes();
	isPlay = true;
	isDelay = true;
	curPlayTime = 0.0f;
	Projectile->Velocity = FVector(0, 0, 0);
	Particle->SetVisibility(true);

	Success = true;
}

void ACBP_SimpleProjectileSkill::SetPointersToWorldPos(AActor* centerActor, bool& success)
{
	if (centerActor == nullptr)
		centerActor = GetInstigator();

	if (GetInstigator() == nullptr)
	{
		success = false;
		return;
	}

	FVector forward = centerActor->GetActorForwardVector() * startPointer.X;
	FVector right = centerActor->GetActorRightVector() * startPointer.Y;
	FVector up = centerActor->GetActorUpVector() * startPointer.Z;

	startPosition = centerActor->GetActorLocation() + forward + right + up;

	forward = centerActor->GetActorForwardVector() * endPointer.X;
	right = centerActor->GetActorRightVector() * endPointer.Y;
	up = centerActor->GetActorUpVector() * endPointer.Z;

	endPosition = centerActor->GetActorLocation() + forward + right + up;

	success = true;

}

void ACBP_SimpleProjectileSkill::SpawnMeshes()
{
	if (meshType == nullptr) return;

	FActorSpawnParameters param;
	SpawnActorUseClass(mesh, meshType, param);

	mesh->SetActorLocation(endPosition - FVector(0, 0, 90));
	mesh->SetActorRotation(RotatorXYZ(0, 0, UKismetMathLibrary::FindLookAtRotation(startPosition, endPosition).Yaw - 90));
}

void ACBP_SimpleProjectileSkill::SetVelocity()
{
	FVector velocity = endPosition - startPosition;

	float length;
	velocity.ToDirectionAndLength(velocity, length);

	playTime = (length / Projectile->InitialSpeed);
	Projectile->Velocity = (velocity * Projectile->InitialSpeed);

}

void ACBP_SimpleProjectileSkill::SetStart()
{

}

void ACBP_SimpleProjectileSkill::SetEnd()
{

}
