// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/SimulationObject/Interaction_Object/Case/CBP_Dual_WeaponCase.h"

#include "Components/ShapeComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"

#include "Macro/MathMacro.h"

ACBP_Dual_WeaponCase::ACBP_Dual_WeaponCase()
{
	Set_Simul_ComponentsBase(EMeshType::None, ESimulationType::Box, ECollisionType::Sphere);

	Cast<UBoxComponent>(simulationComponent)->SetBoxExtent(FVector(40, 10, 70));
	simulationComponent->SetCollisionProfileName(FName("Weapon"));

	pairWeaponSocket->SetRelativeLocation(FVector(-26, 0, -54));
	pairWeaponSocket->SetRelativeRotation(RotatorXYZ(0, -24.3f, 0));

	mainWeaponSocket->SetRelativeLocation(FVector(26, 0, -54));
	mainWeaponSocket->SetRelativeRotation(RotatorXYZ(0, 24.3f, 0));

	Cast<USphereComponent>(interactionComponent)->SetSphereRadius(96);

	widgetName = FString("DualBlade");
}