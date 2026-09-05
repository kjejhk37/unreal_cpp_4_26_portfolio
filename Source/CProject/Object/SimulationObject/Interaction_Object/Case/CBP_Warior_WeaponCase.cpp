// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/SimulationObject/Interaction_Object/Case/CBP_Warior_WeaponCase.h"
#include "Components/ShapeComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"

#include "Macro/MathMacro.h"

ACBP_Warior_WeaponCase::ACBP_Warior_WeaponCase()
{
	Set_Simul_ComponentsBase(EMeshType::None, ESimulationType::Box, ECollisionType::Sphere);

	Cast<UBoxComponent>(simulationComponent)->SetBoxExtent(FVector(10, 35, 70));
	simulationComponent->SetCollisionProfileName(FName("Weapon"));

	mainWeaponSocket->SetRelativeLocation(FVector(0, 0, -50));
	mainWeaponSocket->SetRelativeRotation(RotatorXYZ(0, 90, 0));

	Cast<USphereComponent>(interactionComponent)->SetSphereRadius(70);

	widgetName = FString("Warrior");
}