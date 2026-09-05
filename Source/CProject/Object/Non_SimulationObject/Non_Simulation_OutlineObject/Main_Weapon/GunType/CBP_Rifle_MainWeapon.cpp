// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/Main_Weapon/GunType/CBP_Rifle_MainWeapon.h"

ACBP_Rifle_MainWeapon::ACBP_Rifle_MainWeapon()
{
	Set_NonSimul_ComponentsBase(EMeshType::SkeletalMesh, ECollisionType::None);
}