// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/SimulationObject/Interaction_Object/MoveObject/KeyObject/CBP_Bust_KeyObject.h"

ACBP_Bust_KeyObject::ACBP_Bust_KeyObject()
{
	Set_Simul_ComponentsBase(EMeshType::StaticMesh, ESimulationType::Box, ECollisionType::Sphere);
}