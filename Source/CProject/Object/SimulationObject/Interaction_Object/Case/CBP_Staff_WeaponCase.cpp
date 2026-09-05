// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/SimulationObject/Interaction_Object/Case/CBP_Staff_WeaponCase.h"

#include "Components/ShapeComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"

#include "Macro/MathMacro.h"

ACBP_Staff_WeaponCase::ACBP_Staff_WeaponCase()
{
	Set_Simul_ComponentsBase(EMeshType::None, ESimulationType::Capsule, ECollisionType::Sphere);

	Cast<UCapsuleComponent>(simulationComponent)->SetCapsuleRadius(20);
	Cast<UCapsuleComponent>(simulationComponent)->SetCapsuleHalfHeight(70);

	simulationComponent->SetCollisionProfileName(FName("Weapon"));

//	pairWeaponSocket->SetRelativeLocation(FVector(-26, 0, -54));
//	pairWeaponSocket->SetRelativeRotation(RotatorXYZ(0, -24.3f, 0));
//
	mainWeaponSocket->SetRelativeLocation(FVector(0, 0, -70));
//	mainWeaponSocket->SetRelativeRotation(RotatorXYZ(0, 24.3f, 0));

	Cast<USphereComponent>(interactionComponent)->SetSphereRadius(96);

	widgetName = FString("Staff");
}