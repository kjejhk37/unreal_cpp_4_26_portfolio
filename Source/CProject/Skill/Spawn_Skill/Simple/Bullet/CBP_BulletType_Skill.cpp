// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Spawn_Skill/Simple/Bullet/CBP_BulletType_Skill.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Character/CBP_Character.h"
#include "Character/Player/CBP_Player.h"


#include "Macro/MyMacro.h"
#include "Macro/MathMacro.h"
#include "Macro/IncludeMacro.h"
#include "Macro/KismetMacro.h"
#include "Kismet/GameplayStatics.h"

#include GunMainWeaponPath
#include "Skill/Spawn_Skill/Spawn_Gun/CBP_Spawn_Gun_Skill.h"

#include "Logger/Logger.h"


ACBP_BulletType_Skill::ACBP_BulletType_Skill()
{

}

void ACBP_BulletType_Skill::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}

void ACBP_BulletType_Skill::BeginPlay()
{
	Super::BeginPlay();

	attackCollsiion->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentBeginOverlap);
}

void ACBP_BulletType_Skill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACBP_BulletType_Skill::Play(bool const InSuccess, bool& Success)
{
	//	Super::Play(InSuccess, Success);

	if (GetOwner() == nullptr) return;

	FVector shotLocation;
	FRotator shotRotator;

	if (ACBP_GunType_MainWeapon* gun = Cast<ACBP_GunType_MainWeapon>(GetOwner()))
	{
		switch (gun->meshType)
		{
		case EMeshType::StaticMesh:
			shotLocation = gun->staticMesh->GetSocketLocation(shotSocket);
			shotRotator = gun->staticMesh->GetSocketRotation(shotSocket);
			break;
		case EMeshType::SkeletalMesh:
			shotLocation = gun->skeletalMesh->GetSocketLocation(shotSocket);
			shotRotator = gun->skeletalMesh->GetSocketRotation(shotSocket);
			break;

		}
	}
	else if(ACBP_Spawn_Gun_Skill* skill = Cast<ACBP_Spawn_Gun_Skill>(GetOwner()))
	{
		shotLocation = skill->GunMesh->GetSocketLocation(shotSocket);
		shotRotator = skill->GunMesh->GetSocketRotation(shotSocket);
	}

	SetActorLocation(shotLocation);

	if (ACBP_Player* player = Cast<ACBP_Player>(GetInstigator()))
	{
		if (ACBP_GunType_MainWeapon* gun = Cast<ACBP_GunType_MainWeapon>(GetOwner()))
		{
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

			shotRotator = UKismetMathLibrary::FindLookAtRotation(shotLocation, aimLocation);
		}
	}
	else
	{
		if (ACBP_Character* character = Cast<ACBP_Character>(GetInstigator()))
		{
			if (character->target != nullptr)
			{
				FVector aimLocation = character->target->GetActorLocation();
				shotRotator = UKismetMathLibrary::FindLookAtRotation(shotLocation, aimLocation);
			}
		}

	}
	

	SetActorRotation(shotRotator);

	FVector velocity = GetActorForwardVector();
	Projectile->Velocity = velocity * bulletSpeed;

	SetStart();
}

void ACBP_BulletType_Skill::SetSpawn(AActor* centerActor)
{
	//	Super::SetSpawn();
	if (GetInstigator() == nullptr) return;

//	Projectile->Deactivate();

	guardSerchType = EGuardSerchType::Owner;
}

void ACBP_BulletType_Skill::SetMesh(EMeshType newMeshType)
{
	Super::SetMesh(newMeshType);

	CreateDefaultSubobjectAuto(Particle);
	CreateDefaultSubobjectAuto(Projectile);
//	CreateDefaultSubobjectAuto(attackCollsiion);

	switch (attackCollisionType)
	{
	case ECollisionType::Capsule:
		attackCollsiion = CreateDefaultSubobject<UCapsuleComponent>("attackCollsiion");
		break;
	case ECollisionType::Sphere:
		attackCollsiion = CreateDefaultSubobject<USphereComponent>("attackCollsiion");
		break;
	case ECollisionType::Box:
		attackCollsiion = CreateDefaultSubobject<UBoxComponent>("attackCollsiion");
		break;
	}

	FAttachmentTransformRules const Rules(EAttachmentRule::KeepRelative, true);

	switch (meshType)
	{
	case EMeshType::StaticMesh:
		Particle->SetupAttachment(staticMesh);
		attackCollsiion->SetupAttachment(staticMesh);
		break;
	case EMeshType::SkeletalMesh:
		Particle->SetupAttachment(skeletalMesh);
		attackCollsiion->SetupAttachment(skeletalMesh);
		break;
	}

	attackCollsiion->SetCollisionProfileName(FName("Shot"));
	attackCollsiion->SetCollisionEnabled(ECollisionEnabled::NoCollision);
//	attackCollsiion->SetSphereRadius(5);

	Projectile->ProjectileGravityScale = 0.0f;
	Projectile->InitialSpeed = 0;
	Projectile->MaxSpeed = bulletSpeed;
	Projectile->Velocity = FVector(0, 0, 0);

	Projectile->bRotationFollowsVelocity = true;

}

void ACBP_BulletType_Skill::SetStart()
{
	Particle->Activate(true);
	attackCollsiion->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	KismetDelay(TEXT("ArrowDelete"), this, 10);
}

void ACBP_BulletType_Skill::ArrowDelete()
{
	Particle->Deactivate();
	DestroyActor(this);
}

void ACBP_BulletType_Skill::SetEnd()
{
	Particle->EndTrails();

}

void ACBP_BulletType_Skill::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ACBP_Character* character = Cast<ACBP_Character>(OtherActor);
	if (character == nullptr)
	{
		attackCollsiion->SetCollisionEnabled(ECollisionEnabled::NoCollision);

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


		DestroyActor(this);
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

