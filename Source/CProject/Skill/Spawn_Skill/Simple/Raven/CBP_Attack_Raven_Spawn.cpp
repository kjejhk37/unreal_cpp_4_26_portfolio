// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Spawn_Skill/Simple/Raven/CBP_Attack_Raven_Spawn.h"
#include "Particles/ParticleSystemComponent.h"
#include "Character/CBP_Character.h"

#include "Macro/MyMacro.h"

#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"

#include "Logger/Logger.h"

ACBP_Attack_Raven_Spawn::ACBP_Attack_Raven_Spawn()
{
	SetMesh(EMeshType::SkeletalMesh);

	CreateDefaultSubobjectAuto(particle);
	particle->SetupAttachment(GetRootComponent());
	particle->SetRelativeScale3D(FVector(6, 6, 6));

	CreateDefaultSubobjectAuto(AttackComponent);
	AttackComponent->SetupAttachment(GetRootComponent());

	skeletalMesh->SetRelativeLocation(FVector(0, 0, 300));
	skeletalMesh->SetRelativeRotation(FRotator(0, -90, 0));
	skeletalMesh->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));

	AttackComponent->SetSphereRadius(500);
	AttackComponent->SetCollisionProfileName(FName("Attack"));
}