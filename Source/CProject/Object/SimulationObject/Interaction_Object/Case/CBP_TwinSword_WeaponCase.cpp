// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/SimulationObject/Interaction_Object/Case/CBP_TwinSword_WeaponCase.h"
#include "Components/ShapeComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"

#include "Macro/MathMacro.h"


ACBP_TwinSword_WeaponCase::ACBP_TwinSword_WeaponCase()
{
	Set_Simul_ComponentsBase(EMeshType::None, ESimulationType::Box, ECollisionType::Sphere);

	Cast<UBoxComponent>(simulationComponent)->SetBoxExtent(FVector(70, 10, 10));
	simulationComponent->SetCollisionProfileName(FName("Weapon"));

	pairWeaponSocket->SetRelativeLocation(FVector(-50, -5, 0));
//	pairWeaponSocket->SetRelativeRotation(RotatorXYZ(0, 0, 0));

	mainWeaponSocket->SetRelativeLocation(FVector(-50, 5, -0));
//	mainWeaponSocket->SetRelativeRotation(RotatorXYZ(0, 24.3f, 0));

	Cast<USphereComponent>(interactionComponent)->SetSphereRadius(70);

	widgetName = FString("TwinSword");
}