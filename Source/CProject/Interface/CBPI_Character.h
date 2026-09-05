// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enums/EWeapon.h"
#include "Enums/EItem.h"
#include "Enums/ECharacter.h"
#include "CBPI_Character.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCBPI_Character : public UInterface
{
	GENERATED_BODY()
};

class CPROJECT_API ICBPI_Character
{
	GENERATED_BODY()
		
public:
	// 이거는 나중에 Character.h에서 직업해야함 여기서하면 터짐
//	UFUNCTION(BlueprintCallable, Category = "Skill")
	virtual void Skill(ESkillType InSkillType, bool isPressed) PURE_VIRTUAL(ICBPI_Character::Skill, return;);
	
	// Action
	virtual void ActionDodge() PURE_VIRTUAL(ICBPI_Character::ActionDodge, return;);
	virtual void ActionDropping(bool& Success) PURE_VIRTUAL(ICBPI_Character::ActionDropping, return;);
	virtual void GunReLoad() PURE_VIRTUAL(ICBPI_Character::GunReLoad, return;);
	virtual void JumpCharacter() PURE_VIRTUAL(ICBPI_Character::JumpCharacter, return;);
	virtual void Action() PURE_VIRTUAL(ICBPI_Character::Action, return;);
	virtual void EquipOrUnEquip() PURE_VIRTUAL(ICBPI_Character::EquipOrUnEquip, return;);

	// Item
	virtual void UsingItem(EItemName InUsingItemName, int InItemNum , bool& Success)PURE_VIRTUAL(ICBPI_Character::UsingItem, return;);
	virtual void UsingItemNumIncreasing()PURE_VIRTUAL(ICBPI_Character::UsingItemNumIncreasing, return;);

	// Zoom
	virtual void ZoomCameraIn() PURE_VIRTUAL(ICBPI_Character::ZoomCameraIn, return;);
	virtual void ZoomCameraOut() PURE_VIRTUAL(ICBPI_Character::ZoomCameraOut, return;);

	// WeaponSelect
	virtual void WeaponSelect(int InInventoryNum) PURE_VIRTUAL(ICBPI_Character::WeaponSelect, return;);

	// MoveEvent
	virtual void CharacterCrouch(bool InCrouch)PURE_VIRTUAL(ICBPI_Character::CharacterCrouch, return;);
	virtual void CharacterJump(bool InIsJump)PURE_VIRTUAL(ICBPI_Character::CharacterJump, return;);
	virtual void Speaker()PURE_VIRTUAL(ICBPI_Character::Speaker, return;);

	// Other
	virtual void ActionDown() PURE_VIRTUAL(ICBPI_Character::ActionDown, return;);
	virtual void ActionRise() PURE_VIRTUAL(ICBPI_Character::ActionRise, return;);

	virtual void ReSetState()PURE_VIRTUAL(ICBPI_Character::ReSetState, return;);
	virtual void SetDie()PURE_VIRTUAL(ICBPI_Character::SetDie, return;);
	virtual void AddDamage(AActor* WeaponActor , ECharacterDamagedType& damageType, F_Hp_Update_Value& resultDamage)PURE_VIRTUAL(ICBPI_Character::AddDamage, return;);
	virtual void UpdateHpWidget()PURE_VIRTUAL(ICBPI_Character::UpdateHpWidget, return;);

	// AI 전용
	virtual void CheckTarget()PURE_VIRTUAL(ICBPI_Character::CheckTarget, return;);

	// Player전용
	virtual void UpdateInterface(EPlayerInterfaceUpdate updateType)PURE_VIRTUAL(ICBPI_Character::UpdateInterface, return;);
	virtual void Parkour() PURE_VIRTUAL(ICBPI_Character::Parkour, return;);
	// Interaction
	virtual void Interaction() PURE_VIRTUAL(ICBPI_Character::Interaciton, return;);
	virtual void InteractionSelect(float Value) PURE_VIRTUAL(ICBPI_Character::InteractionSelect, return;);
};
