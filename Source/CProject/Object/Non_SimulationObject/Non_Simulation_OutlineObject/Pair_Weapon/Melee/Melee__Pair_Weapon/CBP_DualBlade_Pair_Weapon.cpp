// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/Pair_Weapon/Melee/Melee__Pair_Weapon/CBP_DualBlade_Pair_Weapon.h"
#include "Components/CapsuleComponent.h"

ACBP_DualBlade_Pair_Weapon::ACBP_DualBlade_Pair_Weapon()
{
	Set_NonSimul_ComponentsBase(EMeshType::StaticMesh, ECollisionType::None);

	staticMesh->SetCollisionProfileName(FName("NoCollision"));

	Cast<UCapsuleComponent>(attackComponent)->SetCapsuleHalfHeight(70);
	Cast<UCapsuleComponent>(attackComponent)->SetCapsuleRadius(6);

	attackComponent->SetRelativeLocation(FVector(0, 0, 95));

	Trail_Start_Socket = FName("Trail_Start");
	Trail_End_Socket = FName("Trail_End");

	pair_Weapon_Scale = FVector(1, 1, 1);
}

void ACBP_DualBlade_Pair_Weapon::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);
}

void ACBP_DualBlade_Pair_Weapon::Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType)
{
	attackCollisionType = ECollisionType::Capsule;
	Super::Set_NonSimul_ComponentsBase(newMeshType, newInteractionType);
}

void ACBP_DualBlade_Pair_Weapon::BeginPlay()
{
	Super::BeginPlay();
}

void ACBP_DualBlade_Pair_Weapon::Activate(bool InSuccess, bool & OutSuccess)
{
	Super::Activate(InSuccess, OutSuccess);
}

void ACBP_DualBlade_Pair_Weapon::DeActivate(bool InSuccess, bool & OutSuccess)
{
	Super::DeActivate(InSuccess, OutSuccess);
}

void ACBP_DualBlade_Pair_Weapon::TrailParticleActivate()
{
	Super::TrailParticleActivate();
}

void ACBP_DualBlade_Pair_Weapon::TrailParticleDeActivate()
{
	Super::TrailParticleDeActivate();
}
