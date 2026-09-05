// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/NS_InteractionObject/Animation_Object/CBP_ParkourAnimationObject.h"

ACBP_ParkourAnimationObject::ACBP_ParkourAnimationObject()
{
	Set_NonSimul_ComponentsBase(EMeshType::StaticMesh, ECollisionType::Box);
}

void ACBP_ParkourAnimationObject::BeginPlay()
{
	Super::BeginPlay();

	switch (meshType)
	{
	case EMeshType::StaticMesh:
		staticMesh->SetRelativeTransform(FTransform());
		break;
	case EMeshType::SkeletalMesh:
		skeletalMesh->SetRelativeTransform(FTransform());
		break;
	}
}