// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/Main_Weapon/MagicType/CBP_MagicWeapon.h"
#include "Particles/ParticleSystemComponent.h"

#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ShapeComponent.h"

#include "Macro/MyMacro.h"

ACBP_MagicWeapon::ACBP_MagicWeapon()
{
	
}

void ACBP_MagicWeapon::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);
}

void ACBP_MagicWeapon::Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType)
{
	Super::Set_NonSimul_ComponentsBase(newMeshType, newInteractionType);

	CreateDefaultSubobjectAuto(particleSystem);

	switch (meshType)
	{
	case EMeshType::StaticMesh:
		particleSystem->SetupAttachment(staticMesh);
		break;
	case EMeshType::SkeletalMesh:
		particleSystem->SetupAttachment(skeletalMesh);
		break;
	}

}

void ACBP_MagicWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ACBP_MagicWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACBP_MagicWeapon::Activate(bool InSuccess, bool & OutSuccess)
{
//	Super::Activate(InSuccess, OutSuccess);
	TrailParticleActivate();
}

void ACBP_MagicWeapon::DeActivate(bool InSuccess, bool & OutSuccess)
{
//	Super::DeActivate(InSuccess, OutSuccess);
	TrailParticleDeActivate();
}

void ACBP_MagicWeapon::TrailParticleActivate()
{
	particleSystem->Activate();
}

void ACBP_MagicWeapon::TrailParticleDeActivate()
{
}
