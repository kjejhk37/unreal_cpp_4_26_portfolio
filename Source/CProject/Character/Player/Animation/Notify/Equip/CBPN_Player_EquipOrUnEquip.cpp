// Fill out your copyright notice in the Description page of Project Settings.


#include "CBPN_Player_EquipOrUnEquip.h"
#include "Character/CBP_Character.h"
#include "Character/Player/CBP_PlayerController.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "Macro/IncludeMacro.h"

#include "Logger/Logger.h"

#include MainWeaponPath
#include PairWeaponPath

UCBPN_Player_EquipOrUnEquip::UCBPN_Player_EquipOrUnEquip()
{
	NotifyName = FName("EquipOrUnEquip");
}

FString UCBPN_Player_EquipOrUnEquip::GetNotifyName_Implementation() const
{
	return NotifyName.ToString();
}

void UCBPN_Player_EquipOrUnEquip::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	// 여기서 mainWeapon, pairWeapon을 손에 붙여주고 셋팅도 해줌

	ACBP_Character* character = Cast<ACBP_Character>(MeshComp->GetOwner());
	if (character == nullptr) return;

	bool isEquip = true;
	character->IsCharacterState(ECharacterState::UnEquip, isEquip);

	ACBP_MainWeapon* mainWeapon = Cast<ACBP_MainWeapon>(character->main_Weapon);
	ACBP_PairWeapon* pairWeapon = Cast<ACBP_PairWeapon>(character->pair_Weapon);

	if (isEquip)
	{
		if (mainWeapon != nullptr)
		{
			mainWeapon->SetEquip(character,false);
		}

		if (pairWeapon != nullptr)
		{
			pairWeapon->SetEquip(false);
		}

		character->main_Weapon = nullptr;
		character->pair_Weapon = nullptr;
	}
	else
	{
		if (mainWeapon != nullptr)
		{
			mainWeapon->SetEquip(character, false);
		}

		if (pairWeapon != nullptr)
		{
			pairWeapon->SetEquip(false);
		}

		character->main_Weapon = character->weapon_Inventory[character->cur_Using_Weapon_Num];

		if (ACBP_MainWeapon* castMainWeapon = Cast<ACBP_MainWeapon>(character->main_Weapon))
		{
			character->pair_Weapon = castMainWeapon->pairWeapon;

			castMainWeapon->SetEquip(character, true);

			if (ACBP_PairWeapon* castPairWeapon = Cast<ACBP_PairWeapon>(character->pair_Weapon))
			{
				castPairWeapon->SetEquip(true);
			}
		}

	}

	character->UpdateInterface(EPlayerInterfaceUpdate::Weapon_Inventory);

	ACBP_MainWeapon* curMainWeapon = Cast<ACBP_MainWeapon>(character->main_Weapon);
	if (curMainWeapon == nullptr)
	{
		character->GetCharacterMovement()->bOrientRotationToMovement = true;
		return;
	}

	EWeaponName weaponName = curMainWeapon->weaponName;
	bool bSetOrient = true;
	
	switch (weaponName)
	{
	case EWeaponName::Bow:
	case EWeaponName::Rifle:
		bSetOrient = false;
		break;
	}

	character->GetCharacterMovement()->bOrientRotationToMovement = bSetOrient;

}