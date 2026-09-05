// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/SimulationObject/Interaction_Object/Case/CBP_Bow_WeaponCase.h"
#include "Components/ShapeComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"

ACBP_Bow_WeaponCase::ACBP_Bow_WeaponCase()
{
	Set_Simul_ComponentsBase(EMeshType::None, ESimulationType::Box, ECollisionType::Sphere);

	Cast<UBoxComponent>(simulationComponent)->SetBoxExtent(FVector(20, 10, 90));
	simulationComponent->SetCollisionProfileName(FName("Weapon"));

	Cast<USphereComponent>(interactionComponent)->SetSphereRadius(96);

	widgetName = FString("Bow");
}