// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/Pair_Weapon/Shield/CBP_PairWeapon_Shield.h"
#include "Character/CBP_Character.h"
#include "Particles/ParticleSystemComponent.h"


#include "Components/BoxComponent.h"
#include "Components/ShapeComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"

#include "Macro/IncludeMacro.h"
#include "Macro/MyMacro.h"

#include "Logger/Logger.h"

#include MainWeaponPath

ACBP_PairWeapon_Shield::ACBP_PairWeapon_Shield()
{

}

void ACBP_PairWeapon_Shield::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ACBP_PairWeapon_Shield::BeginPlay()
{
	Super::BeginPlay();
}

void ACBP_PairWeapon_Shield::Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType)
{
	Super::Set_NonSimul_ComponentsBase(newMeshType, newInteractionType);

	CreateDefaultSubobjectAuto(particleSystem);
	CreateDefaultSubobjectAuto(ShieldComponent);

	switch (ShieldCollisionType)
	{
	case ECollisionType::Box:
		ShieldComponent = Cast<UShapeComponent>(CreateDefaultSubobject<UBoxComponent>(TEXT("ShieldCollision")));
		break;
	case ECollisionType::Sphere:
		ShieldComponent = Cast<UShapeComponent>(CreateDefaultSubobject<USphereComponent>(TEXT("ShieldCollision")));
		break;
	case ECollisionType::Capsule:
		ShieldComponent = Cast<UShapeComponent>(CreateDefaultSubobject<UCapsuleComponent>(TEXT("ShieldCollision")));
		break;
	}


	FAttachmentTransformRules const Rules(EAttachmentRule::KeepRelative, true);

	switch (meshType)
	{
	case EMeshType::StaticMesh:
		ShieldComponent->SetupAttachment(staticMesh);
		particleSystem->SetupAttachment(staticMesh);
		break;
	case EMeshType::SkeletalMesh:
		ShieldComponent->SetupAttachment(skeletalMesh);
		particleSystem->SetupAttachment(skeletalMesh);
		break;
	}

	ShieldComponent->SetCollisionProfileName(FName("Shield"));

}

/* ================================ interface ======================================*/
void ACBP_PairWeapon_Shield::Activate(bool InSuccess, bool& OutSuccess)
{

}

void ACBP_PairWeapon_Shield::DeActivate(bool InSuccess, bool& OutSuccess)
{

}

void ACBP_PairWeapon_Shield::CheckGuard(AActor* const otherActor, bool& canGuard)
{
	// 방패의 콜리전이 상대방 무기의 콜리전과 overrlap되어있는지 확인하여 처리


}