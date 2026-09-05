// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Spawn_Skill/Simple/Homing/CBP_Dual_HormingSkill.h"
#include "Components/CapsuleComponent.h"
#include "Macro/MathMacro.h"

ACBP_Dual_HormingSkill::ACBP_Dual_HormingSkill()
{
	SetMesh(EMeshType::StaticMesh);

	staticMesh->SetRelativeRotation(RotatorXYZ(0, -90, 0));

	Cast<UCapsuleComponent>(attackComponent)->SetCapsuleHalfHeight(50);
	Cast<UCapsuleComponent>(attackComponent)->SetCapsuleRadius(6);

	attackComponent->SetRelativeLocation(FVector(0, 0, 80));

	attackPushType = EAttackPushType::WeaponLocation;
	
}