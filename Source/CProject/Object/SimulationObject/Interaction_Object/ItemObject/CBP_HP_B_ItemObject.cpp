// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/SimulationObject/Interaction_Object/ItemObject/CBP_HP_B_ItemObject.h"

ACBP_HP_B_ItemObject::ACBP_HP_B_ItemObject()
{
	Set_Simul_ComponentsBase(EMeshType::StaticMesh, ESimulationType::Box, ECollisionType::Sphere);
}