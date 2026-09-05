// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Spawn_Skill/Simple/Bullet/CBP_BigBullet_Shot.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Macro/MyMacro.h"
#include "Macro/MathMacro.h"
#include "Macro/IncludeMacro.h"
#include "Macro/KismetMacro.h"
#include "Kismet/GameplayStatics.h"

#include GunMainWeaponPath
#include "Skill/Spawn_Skill/Spawn_Gun/CBP_Spawn_Gun_Skill.h"

#include "Logger/Logger.h"


ACBP_BigBullet_Shot::ACBP_BigBullet_Shot()
{
	attackCollisionType = ECollisionType::Sphere;
	SetMesh(EMeshType::StaticMesh);

	Particle->SetRelativeRotation(RotatorXYZ(0, 90, 0));
	staticMesh->SetRelativeRotation(RotatorXYZ(0, -90, 0));
}

void ACBP_BigBullet_Shot::Play(bool const InSuccess, bool& Success)
{

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
	else if (ACBP_Spawn_Gun_Skill* skill = Cast<ACBP_Spawn_Gun_Skill>(GetOwner()))
	{
		shotLocation = skill->GunMesh->GetSocketLocation(shotSocket);
		shotRotator = skill->GunMesh->GetSocketRotation(shotSocket);
	}

	SetActorLocation(shotLocation);

	SetActorRotation(shotRotator);

	FVector velocity = GetActorForwardVector();
	Projectile->Velocity = velocity * bulletSpeed;

	SetStart();
}