// Fill out your copyright notice in the Description page of Project Settings.


#include "CBP_WarloadSkel_MainWeapon.h"
#include "Components/CapsuleComponent.h"

#include "Macro/MyMacro.h"
#include "Macro/MathMacro.h"

#include "Logger/Logger.h"

ACBP_WarloadSkel_MainWeapon::ACBP_WarloadSkel_MainWeapon()
{
	attackCollisionType = ECollisionType::Capsule;
	Set_NonSimul_ComponentsBase(EMeshType::StaticMesh, ECollisionType::None);

	staticMesh->SetCollisionProfileName(FName("NoCollision"));

	attackComponent->SetRelativeRotation(RotatorXYZ(0, 90, 0));
	attackComponent->SetRelativeLocation(FVector(70, 0, 0));

	Cast<UCapsuleComponent>(attackComponent)->SetCapsuleRadius(5);
	Cast<UCapsuleComponent>(attackComponent)->SetCapsuleHalfHeight(60);

	Trail_Start_Socket = FName("Trail_Start");
	Trail_End_Socket = FName("Trail_End");

	weaponName = EWeaponName::LongSword;
}