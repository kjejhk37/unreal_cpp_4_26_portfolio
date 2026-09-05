
#include "CBP_Character.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Player/CBP_Player.h"
#include "Player/CBP_PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Macro/MyMacro.h"
#include "Macro/IncludeMacro.h"
#include "Macro/MathMacro.h"
#include "Macro/KismetMacro.h"

#include "Logger/Logger.h"

#include MainWeaponPath
#include PairWeaponPath
#include ItemObjectPath

void ACBP_Character::CanArmming(bool& canArmming)
{
	canArmming = false;

	if (cur_ZoomMode) return;
	

	else
	{
		switch (characterState)
		{
		case ECharacterState::Idle:
		case ECharacterState::Jump:
			canArmming = true;
			break;
		}

		return;
	}
}

void ACBP_Character::CanAttack(bool& canAttack)
{
	canAttack = false;

	switch (characterState)
	{
	case ECharacterState::Idle:
		canAttack = true;
		break;

	}

}

void ACBP_Character::CanDamaged(bool& canDamaged)
{
	canDamaged = false;

	if (ACBP_Player* isPlayer = Cast<ACBP_Player>(this))
	{
		switch (characterState)
		{
		case ECharacterState::Idle:
		case ECharacterState::Attack:
		case ECharacterState::UsingItem:
		case ECharacterState::UnEquip:
		case ECharacterState::Equip:
		case ECharacterState::Jump:
		case ECharacterState::Damaged:
		case ECharacterState::Down:
		case ECharacterState::Rise:
		case ECharacterState::ReLoad:
			canDamaged = true;
		}
	}
	else
	{
		switch (characterState)
		{
		case ECharacterState::Idle:
		case ECharacterState::Attack:
		case ECharacterState::UsingItem:
		case ECharacterState::UnEquip:
		case ECharacterState::Equip:
		case ECharacterState::Jump:
		case ECharacterState::Skill:
		case ECharacterState::Damaged:
		case ECharacterState::Down:
		case ECharacterState::Rise:
		case ECharacterState::ReLoad:
			canDamaged = true;
		}
	}
}

void ACBP_Character::CanActionJump(bool& canJump)
{
	canJump = false;

	switch (characterState)
	{
	case ECharacterState::Idle:
	case ECharacterState::UnEquip:
	case ECharacterState::Equip:
		canJump = true;
		break;
	}
}

void ACBP_Character::CanMove(bool& canMove)
{
	canMove = false;

	if (canMoveBase == false) return;

	switch (characterState)
	{
	case ECharacterState::Idle:
		canMove = true;
		break;
	case ECharacterState::Attack:
	case ECharacterState::ReLoad:

		ACBP_MainWeapon* mainWeapon = Cast<ACBP_MainWeapon>(main_Weapon);
		if (mainWeapon == nullptr) return;
		EWeaponName weaponName = mainWeapon->weaponName;

		switch (weaponName)
		{
		case EWeaponName::Bow:
		case EWeaponName::Rifle:
			canMove = true;
			break;
		}
		break;

	}
}

void ACBP_Character::CanDodge(bool& canDodge)
{
	canDodge = true;

	switch (characterState)
	{
	case ECharacterState::Dodge:
	case ECharacterState::Jump:
	case ECharacterState::Dead:
	case ECharacterState::Skill:
		canDodge = false;
		break;
	}

}

void ACBP_Character::CanDropping(bool& canDropping)
{
	canDropping = false;

	if (cur_ZoomMode) return;

	switch (characterState)
	{
	case ECharacterState::Idle:
		canDropping = true;
		break;
	}
}

void ACBP_Character::CanPickUpWeapon(EWeaponName const weaponName, bool& canPickUp)
{
	if (weapon_Inventory.Num() >= max_Weapon_Inventory_Num)
	{
		canPickUp = false;
		return;
	}

	for (auto* actor : weapon_Inventory)
	{
		if (auto* weapon = Cast<ACBP_MainWeapon>(actor))
		{
			if (weapon->weaponName == weaponName)
			{
				canPickUp = false;
				return;
			}
		}
	}

	canPickUp = true;

}

void ACBP_Character::CanAddItem(EItemName const itemName, bool& canAdd)
{
	bool foolInventory = (Item_Inventory.Num() < max_Item_Inventory_Num);

	bool haveItem = false;
	if (Item_Inventory.Contains(itemName) == true)
	{
		haveItem = (Item_Inventory[itemName] > 0);
	}

	canAdd = (foolInventory || haveItem);
}

void ACBP_Character::CanActionSkill(ESkillType const skillType, bool& canAction)
{
	canAction = false;

	if (cur_ZoomMode) return;

	switch (characterState)
	{
	case ECharacterState::Idle:
		canAction = true;
		break;
	}
	
}


void ACBP_Character::AttachActorToCharacter(AActor * const Actor, bool const Equip)
{
	FAttachmentTransformRules const Rules(EAttachmentRule::SnapToTarget, true);

	if (auto* Weapon = Cast<ACBP_MainWeapon>(Actor))
	{
		FName socket = (Equip) ? Weapon->equip_Socket : Weapon->unEquip_Socket;
		Weapon->AttachToComponent(GetMesh(), Rules, socket);

		return;
	}

	if (auto* Weapon = Cast<ACBP_PairWeapon>(Actor))
	{
		FName socket = (Equip) ? Weapon->equip_Socket : Weapon->unEquip_Socket;
		Weapon->AttachToComponent(GetMesh(), Rules, socket);
		return;
	}

}

void ACBP_Character::AddInventory(bool const willAdd, AActor * const Actor, bool& Success)
{
	Success = false;

	if (!willAdd)
		return;

	if (auto* weapon = Cast<ACBP_MainWeapon>(Actor))
	{
		weapon_Inventory.AddUnique(weapon);
		Success = true;

		if (ACBP_PlayerController* playerController = Cast<ACBP_PlayerController>(GetController()))
		{
			FString string = FString("Add : ") + weapon->widgetString;

			playerController->Interface_TextDraw(FName("AddWeapon"), string, FVector2D(0, -200), true, 1, FVector2D(0, -50));
		}
		
		UpdateInterface(EPlayerInterfaceUpdate::Weapon_Inventory);
	}

	if (auto* item = Cast<ACBP_ItemObject>(Actor))
	{
		EItemName curItemName = item->itemName;
		int newNum = item->itemNum;

		if (Item_Inventory.Contains(curItemName) == true)
		{
			newNum += Item_Inventory[curItemName];
		}

		TTuple<EItemName, int> temp(curItemName, newNum);

		Item_Inventory.Add(temp);

		if (ACBP_PlayerController* playerController = Cast<ACBP_PlayerController>(GetController()))
		{
			FString string = FString("Add : ") + item->widgetString;

			playerController->Interface_TextDraw(FName("AddItem"), string, FVector2D(0, -200), true, 1, FVector2D(0, -50));
		}

		Success = true;
		UpdateInterface(EPlayerInterfaceUpdate::Item_Inventory);
	}


}

void ACBP_Character::IsHostile(ECamp compare, bool& hostile)
{
	hostile = false;

	switch (camp)
	{
	case ECamp::Enemy:
		if (compare != ECamp::Enemy)
		{
			hostile = true;
		}
		break;
	case ECamp::Neutrality:
		break;
	case ECamp::Player:
		if (compare == ECamp::Enemy)
		{
			hostile = true;
		}
		break;
	}


}

void ACBP_Character::IsCharacterState(ECharacterState compare, bool & Same)
{
	Same = (characterState == compare);
}


void ACBP_Character::AddHpUpdate(F_Hp_Update_Value const newAddHp)
{
	hp_Value_Vector.Add(newAddHp);
	SetUnPauseTimer(hpTimerHandle);
}

void ACBP_Character::UpdateHpValue()
{
	float tempHp = curHp;

	TArray<F_Hp_Update_Value> tempHpDataVector;
	bool willPauseTimer = true;

	for (F_Hp_Update_Value& hpData : hp_Value_Vector)
	{
		if (hpData.curUpdateTick == 0)
		{
			tempHp -= hpData.updateValue;
			hpData.updateCount--;
			hpData.curUpdateTick = hpData.maxUpdateTick;
		}
		else
		{
			hpData.curUpdateTick--;
		}

		if (hpData.updateCount != 0) 
		{
			tempHpDataVector.Add(hpData);
			willPauseTimer = false;
		}
	}

	if (willPauseTimer) SetPauseTimer(hpTimerHandle);

	hp_Value_Vector.Empty();
	hp_Value_Vector = tempHpDataVector;
	curHp = UKismetMathLibrary::FClamp(tempHp, 0, maxHp);

	if (curHp <= 0) SetDie();

	UpdateHpWidget();
	UpdateInterface(EPlayerInterfaceUpdate::HP_Gauge);
}


void ACBP_Character::SerchCloseTarget()
{
	FVector centerLocation = GetActorLocation();
	float curTargetLenght = FLT_MAX;


	// 현재 캐릭터가 살아있는지 확인
	if (ACBP_Character* targetCharacter = Cast<ACBP_Character>(target))
	{
		if (targetCharacter->characterState == ECharacterState::Dead)
		{
			targetCandidate.Remove(target);
			target = nullptr;
		}
	}

	if (target != nullptr)
	{
		curTargetLenght = (target->GetActorLocation() - centerLocation).Size();
	}

	TArray<AActor*> willDelateTargetCadidate;

	for (AActor* actor : targetCandidate)
	{
		ACBP_Character* actorCharacter = Cast<ACBP_Character>(actor);
		if (actorCharacter == nullptr)
		{
			willDelateTargetCadidate.Add(actor);
			continue;
		}

		if (actorCharacter->characterState == ECharacterState::Dead)
		{
			willDelateTargetCadidate.Add(actor);
			continue;
		}

		bool bisHostile = false;
		IsHostile(actorCharacter->camp, bisHostile);
		if (bisHostile == false)
		{
			willDelateTargetCadidate.Add(actor);
			continue;
		}

		// 여기까지 왔으면 일단 actor은 존재하며 target은 nullptr일수도 존재할수도있음
		float actorDistance = (centerLocation - actor->GetActorLocation()).Size();

		if (actorDistance < curTargetLenght)
		{
			// 아무튼 더 가까운 것을 찾은것
			target = actor;
		}
	}

	for (AActor* willDeleteActor : willDelateTargetCadidate)
	{
		if(targetCandidate.Contains(willDeleteActor) == true)
			targetCandidate.Remove(willDeleteActor);
	}


	if (targetCandidate.Num() == 0)
	{
		SetPauseTimer(CharacterSerchHandle);
	}

}

/* ============================================================================================*/
void ACBP_Character::SkillSpawn(TSubclassOf<class ACBP_Skill> skillClass, ACBP_Skill*& skill, ESkillType skillType)
{
	if (skillClass == nullptr) return;

	FActorSpawnParameters param;
	param.Owner = main_Weapon;
	param.Instigator = this;

	SpawnActorUseClass(skill, skillClass, param);
	
	skill->skillType = skillType;

	/*
	bool inSuccsee = true;
	bool outSuccess = false;
	skill->Play(inSuccsee, outSuccess);
	*/

	// 눌렀다 때는것은 NotifyState에서 검색하는 것이 나을듯
	// isPressed를 이용하면 꽤나 간단하게 가능할 것으로 예측
	
}

void ACBP_Character::SkillStart()
{
	// Skill이 Play되는 순간에 부를 것
}

void ACBP_Character::SkillEnd()
{
	// Skill이 End되는 순간에 부를 것
//	characterState = ECharacterState::Idle;

}

void ACBP_Character::JumpStart()
{
	FVector velocity = GetVelocity();
	velocity.Z = 0;

	F_BaseMontageData montageData;
	character_MontageDataAsset->GetCharacterMontage(ECharacterMontageName::JumpStart, montageData);

	if (montageData.Montage == nullptr) return;

	PlayMontageCharacter(ThisClass, montageData.Montage, montageData.PlayRate, montageData.Section,
		"JumpStart",
		ThisClass::AddMontageEndedDelegate();
	);

	GetCharacterMovement()->AddImpulse(velocity);
}

void ACBP_Character::JumpEnd()
{
	F_BaseMontageData montageData;
	character_MontageDataAsset->GetCharacterMontage(ECharacterMontageName::JumpEnd, montageData);

	if (montageData.Montage == nullptr) return;

	PlayMontageCharacter(ThisClass, montageData.Montage, montageData.PlayRate, montageData.Section,
		"ReSetState",
		ThisClass::AddMontageEndedDelegate();
	);
}
/*============================================================================================*/
/* ================================ Montage Blend 에 쓰일 것 ==================================*/
void ACBP_Character::ActionBlendOut()
{
	if (!cur_Attack_Is_End)
	{
		cur_Attack_Is_End = true;
		ThisClass::ComboAction();
	}
}

void ACBP_Character::ComboAction()
{
	if (auto* weapon = Cast<ACBP_MainWeapon>(main_Weapon))
	{
		weapon->GetMontageData(characterName, characterState, attack_Count, tempMontageData);

		PlayMontageCharacter(ThisClass, tempMontageData.Montage, tempMontageData.PlayRate, tempMontageData.Section,
			"Action",
			ThisClass::AddMontageEndedDelegate();
			ThisClass::AddMontageBlendOutDelegate();
		);

		attack_Count++;
	}
}

/* ================================ Montage Bind 관련 ================================*/

void ACBP_Character::CharacterOnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	// 방해받으면 bInterrupted = true
	if (bInterrupted) return;

	if (MontageDelegate == FString("ReSetState"))
	{
		ThisClass::ReSetState();
	}
	else if (MontageDelegate == FString("Action"))
	{
		ThisClass::ReSetState();
	}
	else if (MontageDelegate == FString("JumpStart"))
	{
		attack_Count = 0;
		cur_Attack_Is_End = true;
	}
}

void ACBP_Character::CharacterOnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted)
{
	if (bInterrupted) return;

	if (MontageDelegate == FString("ReSetState"))
	{
		ThisClass::ReSetState();
	}
	else if (MontageDelegate == FString("Action"))
	{
		ThisClass::ActionBlendOut();
	}
}
void ACBP_Character::CharacterOnMontageStarted(UAnimMontage* Montage, bool bInterrupted)
{
	if (!bInterrupted) return;

}

void ACBP_Character::CharacterOnPlayMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
}

void ACBP_Character::CharacterOnPlayMontageNotifyEnd(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
}


/* ============================== Clear ==============================================*/
void ACBP_Character::ClearMontageDelegate()
{
	if (!ClearEndDelegate)
	{
		GetMesh()->GetAnimInstance()->OnMontageEnded.Clear();
		ClearEndDelegate = true;
	}

	if (!ClearBeginDelegate)
	{
		GetMesh()->GetAnimInstance()->OnMontageStarted.Clear();
		ClearBeginDelegate = true;
	}

	if (!ClearNotifyBeginDelegate)
	{
		GetMesh()->GetAnimInstance()->OnPlayMontageNotifyBegin.Clear();
		ClearNotifyBeginDelegate = true;
	}

	if (!ClearNotifyEndDelegate)
	{
		GetMesh()->GetAnimInstance()->OnPlayMontageNotifyEnd.Clear();
		ClearNotifyEndDelegate = true;
	}

	if (!ClearBlendOutDelegate)
	{
		GetMesh()->GetAnimInstance()->OnMontageBlendingOut.Clear();
		ClearBlendOutDelegate = true;

		BaseOnMontageBlendingOut();
	}
}

void ACBP_Character::AddMontageEndedDelegate() 
{
	GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &ThisClass::CharacterOnMontageEnded);
	ClearEndDelegate = false;
}

void ACBP_Character::AddMontageStartedDelegate()
{
	GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &ThisClass::CharacterOnMontageStarted);
	ClearBeginDelegate = false;
}

void ACBP_Character::AddMontageNotifyBeginDelegate()
{
	GetMesh()->GetAnimInstance()->OnPlayMontageNotifyBegin.AddDynamic(this, &ThisClass::CharacterOnPlayMontageNotifyBegin);
	ClearNotifyBeginDelegate = false;
}

void ACBP_Character::AddMontageNotifyEndedDelegate()
{
	GetMesh()->GetAnimInstance()->OnPlayMontageNotifyBegin.AddDynamic(this, &ThisClass::CharacterOnPlayMontageNotifyEnd);
	ClearNotifyEndDelegate = false;
}

void ACBP_Character::AddMontageBlendOutDelegate()
{
	GetMesh()->GetAnimInstance()->OnMontageBlendingOut.AddDynamic(this, &ThisClass::CharacterOnMontageBlendingOut);
	ClearBlendOutDelegate = false;
}