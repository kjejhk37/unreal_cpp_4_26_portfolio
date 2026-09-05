// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/Animation/Notify/Attack/CBPN_WeaponActivate_Notify.h"
#include "Character/CBP_Character.h"

#include "Macro/IncludeMacro.h"
#include "Logger/Logger.h"

#include MainWeaponPath
#include PairWeaponPath

UCBPN_WeaponActivate_Notify::UCBPN_WeaponActivate_Notify()
{

}

FString UCBPN_WeaponActivate_Notify::GetNotifyName_Implementation() const
{
	return FString("Weapon_Activate");
}

void UCBPN_WeaponActivate_Notify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	ACBP_Character* character = Cast<ACBP_Character>(MeshComp->GetOwner());
	if (character == nullptr) return;

	if (isMainWeapon)
	{
		ACBP_MainWeapon* mainWeapon = Cast<ACBP_MainWeapon>(character->main_Weapon);
		if (mainWeapon == nullptr) return;


		damage.updateValue += rand() % 10 - 5;


		mainWeapon->SetDamage(damage);
		bool InSuccess = true;
		bool OutSuccess = false;
		mainWeapon->Activate(InSuccess, OutSuccess);

	}
	else
	{
		ACBP_PairWeapon* pairWeapon = Cast<ACBP_PairWeapon>(character->pair_Weapon);
		if (pairWeapon == nullptr) return;

		pairWeapon->SetDamage(damage);
		bool InSuccess = true;
		bool OutSuccess = false;
		pairWeapon->Activate(InSuccess, OutSuccess);
	}

}

void UCBPN_WeaponActivate_Notify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	ACBP_Character* character = Cast<ACBP_Character>(MeshComp->GetOwner());
	if (character == nullptr) return;

	if (isMainWeapon)
	{
		ACBP_MainWeapon* mainWeapon = Cast<ACBP_MainWeapon>(character->main_Weapon);
		if (mainWeapon == nullptr) return;

		bool InSuccess = true;
		bool OutSuccess = false;
		mainWeapon->DeActivate(InSuccess, OutSuccess);

	}
	else
	{
		ACBP_PairWeapon* pairWeapon = Cast<ACBP_PairWeapon>(character->pair_Weapon);
		if (pairWeapon == nullptr) return;

		bool InSuccess = true;
		bool OutSuccess = false;
		pairWeapon->DeActivate(InSuccess, OutSuccess);
	}

}

void UCBPN_WeaponActivate_Notify::NotifyTick(class USkeletalMeshComponent * MeshComp, class UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

}
