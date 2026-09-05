// Fill out your copyright notice in the Description page of Project Settings.


#include "CBP_Melee_Pair_Weapon.h"
#include "Particles/ParticleSystemComponent.h"

#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ShapeComponent.h"

#include "Macro/MyMacro.h"

ACBP_Melee_Pair_Weapon::ACBP_Melee_Pair_Weapon()
{

//	CreateDefaultSubobjectAuto(attackCollision);


}
	
void ACBP_Melee_Pair_Weapon::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}

void ACBP_Melee_Pair_Weapon::Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType)
{
	Super::Set_NonSimul_ComponentsBase(newMeshType, newInteractionType);

	switch (attackCollisionType)
	{
	case ECollisionType::Box:
		attackComponent = Cast<UShapeComponent>(CreateDefaultSubobject<UBoxComponent>(TEXT("AttackCollision")));
		break;
	case ECollisionType::Sphere:
		attackComponent = Cast<UShapeComponent>(CreateDefaultSubobject<USphereComponent>(TEXT("AttackCollision")));
		break;
	case ECollisionType::Capsule:
		attackComponent = Cast<UShapeComponent>(CreateDefaultSubobject<UCapsuleComponent>(TEXT("AttackCollision")));
		break;
	}

	FAttachmentTransformRules const Rules(EAttachmentRule::KeepRelative, true);

	switch (meshType)
	{
	case EMeshType::StaticMesh:
		attackComponent->SetupAttachment(staticMesh);
		break;
	case EMeshType::SkeletalMesh:
		attackComponent->SetupAttachment(skeletalMesh);
		break;
	}

	attackComponent->SetCollisionProfileName(FName("Attack"));

	CreateDefaultSubobjectAuto(particleSystem);

	particleSystem->SetupAttachment(staticMesh);

}

void ACBP_Melee_Pair_Weapon::BeginPlay()
{
	Super::BeginPlay();

}

void ACBP_Melee_Pair_Weapon::TrailParticleActivate()
{
	particleSystem->BeginTrails(Trail_Start_Socket, Trail_End_Socket, ETrailWidthMode::ETrailWidthMode_FromCentre, 1.0f);

}

void ACBP_Melee_Pair_Weapon::TrailParticleDeActivate()
{
	particleSystem->EndTrails();
}

void ACBP_Melee_Pair_Weapon::Activate(bool InSuccess, bool& OutSuccess)
{
	Super::Activate(InSuccess, OutSuccess);

	if (OutSuccess == false) return;

	ThisClass::TrailParticleActivate();
}

void ACBP_Melee_Pair_Weapon::DeActivate(bool InSuccess, bool& OutSuccess)
{
	Super::DeActivate(InSuccess, OutSuccess);

	if (OutSuccess == false) return;

	ThisClass::TrailParticleDeActivate();
}
