// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/Main_Weapon/MeleeType/CBP_Melee_MainWeapon.h"
#include "Particles/ParticleSystemComponent.h"
#include "Character/CBP_Character.h"
#include "Kismet/GameplayStatics.h"


#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ShapeComponent.h"

#include "Macro/MyMacro.h"
#include "Macro/KismetMacro.h"

#include "Logger/Logger.h"

ACBP_Melee_MainWeapon::ACBP_Melee_MainWeapon()
{


}

void ACBP_Melee_MainWeapon::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);
}

void ACBP_Melee_MainWeapon::Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType)
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
	attackComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CreateDefaultSubobjectAuto(particleSystem);

	particleSystem->SetupAttachment(staticMesh);
}

void ACBP_Melee_MainWeapon::BeginPlay()
{
	Super::BeginPlay();

}

void ACBP_Melee_MainWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACBP_Melee_MainWeapon::Activate(bool InSuccess, bool & OutSuccess)
{
	Super::Activate(InSuccess, OutSuccess);

	attackComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	OverlapedActors.Empty();

	TrailParticleActivate();
}

void ACBP_Melee_MainWeapon::DeActivate(bool InSuccess, bool & OutSuccess)
{
	Super::DeActivate(InSuccess, OutSuccess);

	attackComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	TrailParticleDeActivate();
}

void ACBP_Melee_MainWeapon::TrailParticleActivate()
{
	particleSystem->BeginTrails(Trail_Start_Socket, Trail_End_Socket, ETrailWidthMode::ETrailWidthMode_FromCentre, 1.0f);

}

void ACBP_Melee_MainWeapon::TrailParticleDeActivate()
{
	particleSystem->EndTrails();

}
