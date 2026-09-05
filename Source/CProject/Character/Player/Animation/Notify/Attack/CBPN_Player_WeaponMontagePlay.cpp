// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/Animation/Notify/Attack/CBPN_Player_WeaponMontagePlay.h"
#include "Character/CBP_Character.h"
#include "Macro/IncludeMacro.h"

#include MainWeaponPath

#include "Logger/Logger.h"

UCBPN_Player_WeaponMontagePlay::UCBPN_Player_WeaponMontagePlay()
{
	NotifyName = FName("WeaponMontagePlay");
}

FString UCBPN_Player_WeaponMontagePlay::GetNotifyName_Implementation() const
{
	return NotifyName.ToString();
}

void UCBPN_Player_WeaponMontagePlay::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACBP_Character* character = Cast<ACBP_Character>(MeshComp->GetOwner());
	if (character == nullptr) return;

	ACBP_MainWeapon* mainWeapon = Cast<ACBP_MainWeapon>(character->main_Weapon);
	if (mainWeapon == nullptr) return;

	mainWeapon->Shot(ShotNum, GunMontage);
}
