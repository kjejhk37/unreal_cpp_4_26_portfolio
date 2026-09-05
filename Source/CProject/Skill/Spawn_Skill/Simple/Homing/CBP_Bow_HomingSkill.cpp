// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Spawn_Skill/Simple/Homing/CBP_Bow_HomingSkill.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Macro/MathMacro.h"

ACBP_Bow_HomingSkill::ACBP_Bow_HomingSkill()
{
	attackCollisionType = ECollisionType::Sphere;
	SetMesh(EMeshType::StaticMesh);

	Cast<USphereComponent>(attackComponent)->SetSphereRadius(6);

	attackComponent->SetRelativeLocation(FVector(100, 0, 0));

	Trail_Start = FName("Trail_Start");
	Trail_End = FName("Trail_End");

	attackPushType = EAttackPushType::WeaponLocation;

//	attackComponent->SetCollisionProfileName(FName("Shot"));
}