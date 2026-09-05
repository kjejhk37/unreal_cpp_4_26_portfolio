// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Spawn_Skill/Simple/Arrow/CBP_Player_ArrowShot.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Character/CBP_Character.h"
#include "Character/Player/CBP_Player.h"

#include "Macro/MyMacro.h"
#include "Macro/MathMacro.h"
#include "Macro/IncludeMacro.h"
#include "Macro/KismetMacro.h"
#include "Kismet/GameplayStatics.h"

#include BowMainWeaponPath

#include "Logger/Logger.h"


ACBP_Player_ArrowShot::ACBP_Player_ArrowShot()
{
	SetMesh(EMeshType::StaticMesh);
}

void ACBP_Player_ArrowShot::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}

void ACBP_Player_ArrowShot::BeginPlay()
{
	Super::BeginPlay();

	attackCollsiion->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentBeginOverlap);
}

void ACBP_Player_ArrowShot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACBP_Player_ArrowShot::Play(bool const InSuccess, bool& Success)
{
	//	Super::Play(InSuccess, Success);

	if (GetOwner() == nullptr) return;

	FVector shotLocation;
	FRotator shotRotator;

	if (ACBP_BowMainWeapon* bow = Cast<ACBP_BowMainWeapon>(GetOwner()))
	{
		switch (bow->meshType)
		{
		case EMeshType::StaticMesh:
			shotLocation = bow->staticMesh->GetSocketLocation(shotSocket);
			shotRotator = bow->staticMesh->GetSocketRotation(shotSocket);
			break;
		case EMeshType::SkeletalMesh:
			shotLocation = bow->skeletalMesh->GetSocketLocation(shotSocket);
			shotRotator = bow->skeletalMesh->GetSocketRotation(shotSocket);
			break;

		}
	}
	else if(ACBP_Character* character = Cast<ACBP_Character>(GetInstigator()))
	{
		shotLocation = character->GetMesh()->GetSocketLocation(shotSocket);
		shotRotator = character->GetMesh()->GetSocketRotation(shotSocket);
	}

	SetActorLocation(shotLocation);

	if (ACBP_Player* player = Cast<ACBP_Player>(GetInstigator()))
	{
		if (ACBP_BowMainWeapon* bow = Cast<ACBP_BowMainWeapon>(GetOwner()))
		{

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

			float targetLenght = (playerLocation - aimLocation).Size();

			shotRotator = UKismetMathLibrary::FindLookAtRotation(shotLocation, aimLocation);
			shotRotator.Pitch += 0.5f*UKismetMathLibrary::DegAsin((980 * targetLenght) / (arrowSpeed * arrowSpeed));
		}
	}

	SetActorRotation(shotRotator);

	FVector velocity = GetActorForwardVector();
	Projectile->Velocity = velocity * arrowSpeed;

	SetStart();
}

void ACBP_Player_ArrowShot::SetSpawn(AActor* centerActor)
{
	//	Super::SetSpawn();
	if (GetInstigator() == nullptr) return;

	//	Projectile->Deactivate();

	guardSerchType = EGuardSerchType::Actor;
}

void ACBP_Player_ArrowShot::SetMesh(EMeshType newMeshType)
{
	Super::SetMesh(newMeshType);

	CreateDefaultSubobjectAuto(Particle);
	CreateDefaultSubobjectAuto(Arrow);
	CreateDefaultSubobjectAuto(Projectile);
	CreateDefaultSubobjectAuto(attackCollsiion);

	FAttachmentTransformRules const Rules(EAttachmentRule::KeepRelative, true);

	switch (meshType)
	{
	case EMeshType::StaticMesh:
		Particle->SetupAttachment(staticMesh);
		Arrow->SetupAttachment(staticMesh);
		attackCollsiion->SetupAttachment(staticMesh);
		break;
	case EMeshType::SkeletalMesh:
		Particle->SetupAttachment(skeletalMesh);
		Arrow->SetupAttachment(skeletalMesh);
		attackCollsiion->SetupAttachment(skeletalMesh);
		break;
	}

	attackCollsiion->SetCollisionProfileName(FName("Shot"));
	attackCollsiion->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	attackCollsiion->SetRelativeLocation(FVector(100, 0, 0));
	attackCollsiion->SetSphereRadius(5);

	Projectile->ProjectileGravityScale = 1.0f;
	Projectile->InitialSpeed = 0;
	Projectile->MaxSpeed = arrowSpeed;
	Projectile->Velocity = FVector(0, 0, 0);

	Projectile->bRotationFollowsVelocity = true;
}

void ACBP_Player_ArrowShot::SetStart()
{
	Particle->BeginTrails(trail_Start, trail_End, ETrailWidthMode::ETrailWidthMode_FromCentre, 1.0f);
	attackCollsiion->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	KismetDelay(TEXT("ArrowDelete"), this, 10);
}

void ACBP_Player_ArrowShot::ArrowDelete()
{
	Particle->EndTrails();
	DestroyActor(this);
}

void ACBP_Player_ArrowShot::SetEnd()
{
	Particle->EndTrails();

}

void ACBP_Player_ArrowShot::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ACBP_Character* character = Cast<ACBP_Character>(OtherActor);
	if (character == nullptr)
	{
		Projectile->Velocity = FVector(0, 0, 0);
		Projectile->ProjectileGravityScale = 0;
		attackCollsiion->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		return;
	}

	ECharacterDamagedType damageType = ECharacterDamagedType::Failling;
	F_Hp_Update_Value resultDamage;
	character->AddDamage(this, damageType, resultDamage);

	if (damageType == ECharacterDamagedType::Failling) return;

	FTransform transform;
	transform.SetLocation(GetActorLocation());

	if (attackParticle != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), attackParticle, GetActorLocation(),
			FRotator(0, 0, 0), FVector(1, 1, 1), true);
	}

	if (attackParticleActorClass != nullptr)
	{
		ACBP_Particle* particleActor;
		FActorSpawnParameters param;

		SpawnActorUseClass(particleActor, attackParticleActorClass, param);
		particleActor->SetActorLocation(GetActorLocation());

		F_ParticleActorData data;
		data.EndDelayTime = 0;
		data.StartDelayTime = 0;

		particleActor->SetParticlesBase({ data });
		particleActor->Play();
	}

	SetEnd();

	FVector fontColor = FVector(1, 1, 1);
	float fontSize = 24;

	if (character->characterName == ECharacterName::Player)
		fontSize = 30;

	if (damageType == ECharacterDamagedType::Guard)
	{
		fontColor = FVector(1, 1, 0);
		fontSize *= 0.75f;
	}

	SpawnTextActor(
		FString::FromInt(resultDamage.updateValue * resultDamage.updateCount),
		GetActorLocation(),
		fontColor,
		fontSize);

	DestroyActor(this);

}

