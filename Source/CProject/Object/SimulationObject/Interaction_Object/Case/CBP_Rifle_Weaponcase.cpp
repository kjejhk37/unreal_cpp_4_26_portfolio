// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/SimulationObject/Interaction_Object/Case/CBP_Rifle_Weaponcase.h"

#include "Components/ShapeComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"

ACBP_Rifle_Weaponcase::ACBP_Rifle_Weaponcase()
{
	Set_Simul_ComponentsBase(EMeshType::None, ESimulationType::Box, ECollisionType::Sphere);

	Cast<UBoxComponent>(simulationComponent)->SetBoxExtent(FVector(10, 50, 15));
	simulationComponent->SetCollisionProfileName(FName("Weapon"));

	Cast<USphereComponent>(interactionComponent)->SetSphereRadius(96);

	mainWeaponSocket->SetRelativeLocation(FVector(0, -25, -5));

	widgetName = FString("Rifle");
}