// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Non_SimulationObject/AttackTerrain/CBP_Normal_AttackTerrainObject.h"

#include "Components/ShapeComponent.h"
#include "Particles/ParticleSystemComponent.h"

ACBP_Normal_AttackTerrainObject::ACBP_Normal_AttackTerrainObject()
{
	Set_NonSimul_ComponentsBase(EMeshType::StaticMesh, ECollisionType::Box);

}
 
void ACBP_Normal_AttackTerrainObject::BeginPlay()
{
	Super::BeginPlay();
	particleComponent->SetRelativeLocation(FVector(-750, 0, 0));
	attackComponent->SetRelativeLocation(FVector(0, 0, 0));
}