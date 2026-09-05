// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/SimulationObject/Interaction_Object/Case/CBP_WeaponCase.h"

#include "Components/ShapeComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"

#include "Macro/MyMacro.h"
#include "Macro/MathMacro.h"
#include "Macro/IncludeMacro.h"

#include MainWeaponPath
#include PairWeaponPath
#include "Character/CBP_Character.h"

#include "Logger/Logger.h"


ACBP_WeaponCase::ACBP_WeaponCase()
{

}

void ACBP_WeaponCase::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);
}

void ACBP_WeaponCase::BeginPlay()
{
	Super::BeginPlay();

	ACBP_MainWeapon* mainWeapon = Cast<ACBP_MainWeapon>(mainWeaponSocket->GetChildActor());
	if (mainWeapon == nullptr) return;

	mainWeapon->weaponCase = this;

	ACBP_PairWeapon* pairWeapon = Cast<ACBP_PairWeapon>(pairWeaponSocket->GetChildActor());
	if (pairWeapon == nullptr) return;

	mainWeapon->pairWeapon = pairWeapon;
}

void ACBP_WeaponCase::Set_Simul_ComponentsBase(EMeshType newMeshType, ESimulationType newSimulationType, ECollisionType newInteractionType)
{
	Super::Set_Simul_ComponentsBase(newMeshType, newSimulationType, newInteractionType);

	CreateDefaultSubobjectAuto(mainWeaponSocket);
	CreateDefaultSubobjectAuto(pairWeaponSocket);

	if (simulationType != ESimulationType::None)
	{
		mainWeaponSocket->SetupAttachment(simulationComponent);
		pairWeaponSocket->SetupAttachment(simulationComponent);
	}
}

void ACBP_WeaponCase::Interaction(AActor * const InteractionActor, bool & Success, AActor *& ResultActor)
{
	Super::Interaction(InteractionActor, Success, ResultActor);

	Success = false;
	ResultActor = nullptr;

	ACBP_Character* character = Cast<ACBP_Character>(InteractionActor);
	if (character == nullptr) return;

	ACBP_MainWeapon* mainWeapon = Cast<ACBP_MainWeapon>(mainWeaponSocket->GetChildActor());
	if (mainWeapon == nullptr) return;

	bool canPickUp;
	character->CanPickUpWeapon(mainWeapon->weaponName, canPickUp);

	if (canPickUp == false)
	{
		return;
	}

	bool success;
	mainWeapon->PickUpWeapon(character, success);

	Success = success;

	if (success == false)
	{
		ResultActor = nullptr;
		return;
	}

//	DestroyActor(this);
	ResultActor = mainWeapon;

	SetSimulation(false);
	SetInteractionCollision(ECollisionEnabled::NoCollision);

}

void ACBP_WeaponCase::SetDropping(FVector newLocation, FVector impulseVector, float power)
{
	SetSimulation(true);
	SetInteractionCollision(ECollisionEnabled::QueryAndPhysics);

	SetActorLocation(newLocation);
	SetImpulse(false, power, impulseVector, newLocation);

}