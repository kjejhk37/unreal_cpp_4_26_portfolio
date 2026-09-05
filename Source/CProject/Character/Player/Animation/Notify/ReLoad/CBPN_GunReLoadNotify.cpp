// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/Animation/Notify/ReLoad/CBPN_GunReLoadNotify.h"

#include "Character/CBP_Character.h"

#include "Macro/IncludeMacro.h"

#include GunMainWeaponPath

#include "Logger/Logger.h"

UCBPN_GunReLoadNotify::UCBPN_GunReLoadNotify()
{
	NotifyName = FName("GunReLoad");
}

FString UCBPN_GunReLoadNotify::GetNotifyName_Implementation() const
{
	return NotifyName.ToString();
}

void UCBPN_GunReLoadNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACBP_Character* character = Cast<ACBP_Character>(MeshComp->GetOwner());

	if (character == nullptr) return;

	ACBP_GunType_MainWeapon* gunWeapon = Cast<ACBP_GunType_MainWeapon>(character->main_Weapon);
	if (gunWeapon == nullptr) return;

	bool success = true;
	gunWeapon->ReLoad(success);
}
