// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/Pair_Weapon/Melee/Melee__Pair_Weapon/CBP_TwinSword_Pair_Weapon.h"
#include "Components/CapsuleComponent.h"

#include "Macro/MathMacro.h"

ACBP_TwinSword_Pair_Weapon::ACBP_TwinSword_Pair_Weapon()
{
	Set_NonSimul_ComponentsBase(EMeshType::StaticMesh, ECollisionType::None);

	staticMesh->SetCollisionProfileName(FName("NoCollision"));

	Cast<UCapsuleComponent>(attackComponent)->SetCapsuleHalfHeight(60);
	Cast<UCapsuleComponent>(attackComponent)->SetCapsuleRadius(6);

	attackComponent->SetRelativeLocation(FVector(78.5f, 0, 0));
	attackComponent->SetRelativeRotation(RotatorXYZ(0, 90, 0));

	Trail_Start_Socket = FName("Trail_Start");
	Trail_End_Socket = FName("Trail_End");

	pair_Weapon_Scale = FVector(1, 1, 1);
}

void ACBP_TwinSword_Pair_Weapon::Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType)
{
	attackCollisionType = ECollisionType::Capsule;
	Super::Set_NonSimul_ComponentsBase(newMeshType, newInteractionType);
}
