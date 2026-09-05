// Fill out your copyright notice in the Description page of Project Settings.


#include "CBP_SorcererSkel_MainWeapon.h"
#include "Particles/ParticleSystemComponent.h"

#include "Logger/Logger.h"

ACBP_SorcererSkel_MainWeapon::ACBP_SorcererSkel_MainWeapon()
{
	Set_NonSimul_ComponentsBase(EMeshType::StaticMesh, ECollisionType::None);

	particleSystem->SetRelativeLocation(FVector(0, 0, 35));

	staticMesh->SetCollisionProfileName(FName("NoCollision"));

	main_Weapon_Scale = FVector(4, 4, 4);

	weaponName = EWeaponName::Staff;
}

void ACBP_SorcererSkel_MainWeapon::BeginPlay()
{
	Super::BeginPlay();
}