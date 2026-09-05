// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/Pair_Weapon/Shield/FootmanShield/CBP_FootmanSkel_ShieldPairWeapon.h"
#include "Components/BoxComponent.h"
#include "Components/ShapeComponent.h"

ACBP_FootmanSkel_ShieldPairWeapon::ACBP_FootmanSkel_ShieldPairWeapon()
{
	ShieldCollisionType = ECollisionType::Box;
	Set_NonSimul_ComponentsBase(EMeshType::StaticMesh, ECollisionType::None);

	staticMesh->SetCollisionProfileName(FName("NoCollision"));
	Cast<UBoxComponent>(ShieldComponent)->SetBoxExtent(FVector(5, 72, 72));

}