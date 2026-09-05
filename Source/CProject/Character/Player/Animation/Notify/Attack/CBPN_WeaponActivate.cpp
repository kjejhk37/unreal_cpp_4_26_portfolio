// Fill out your copyright notice in the Description page of Project Settings.


#include "CBPN_WeaponActivate.h"
#include "Logger/Logger.h"
#include "Character/CBP_Character.h"
#include "Interface/CBPI_Weapon.h"

UCBPN_WeaponActivate::UCBPN_WeaponActivate()
{
	NotifyName = FName("WeaponActivate Or DeActivate");
}

FString UCBPN_WeaponActivate::GetNotifyName_Implementation() const
{
	return NotifyName.ToString();
}

void UCBPN_WeaponActivate::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACBP_Character* character = Cast<ACBP_Character>(MeshComp->GetOwner());
	if (character == nullptr) return;

	ICBPI_Weapon* weapon = Cast<ICBPI_Weapon>(((isPairWeapon) ? character->pair_Weapon :character->main_Weapon));
	if (weapon == nullptr) return;

	bool success;

	if (isActivate)
		weapon->Activate(true, success);
	else
		weapon->DeActivate(true, success);
}