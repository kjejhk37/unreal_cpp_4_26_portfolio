// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Spawn_Skill/Simple/Homing/CBP_Butterfly_HomingSkill.h"
#include "Particles/ParticleSystemComponent.h"

#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Macro/MathMacro.h"

ACBP_Butterfly_HomingSkill::ACBP_Butterfly_HomingSkill()
{
	attackCollisionType = ECollisionType::Sphere;
	SetMesh(EMeshType::SkeletalMesh);

	skeletalMesh->SetRelativeRotation(RotatorXYZ(0, 0, -90));
	skeletalMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	Cast<USphereComponent>(attackComponent)->SetSphereRadius(30);
	attackComponent->SetRelativeLocation(FVector(0, 0, 15));


	particle->SetRelativeRotation(RotatorXYZ(0, 0, 90));

	attackPushType = EAttackPushType::WeaponLocation;
}