// Fill out your copyright notice in the Description page of Project Settings.


#include "CBP_Character.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Skill/CBP_Skill.h"
#include "UI/CBP_TextActor.h"
#include "Player/CBP_Player.h"
#include "Player/CBP_PlayerController.h"

#include "Macro/KismetMacro.h"
#include "Macro/MyMacro.h"
#include "Macro/IncludeMacro.h"
#include "Macro/MathMacro.h"

#include "Logger/Logger.h"

#include "PlayMontageCallbackProxy.h"

#include "Interface/CBPI_CanGetAttackDataObject.h"

#include MainWeaponPath
#include PairWeaponPath
#include GunMainWeaponPath

// Sets default values
ACBP_Character::ACBP_Character()
{
	PrimaryActorTick.bCanEverTick = true;

	CreateDefaultSubobjectAuto(InteractionCollision);
	CreateDefaultSubobjectAuto(center);
	center->SetupAttachment(GetRootComponent());

	CreateDefaultSubobjectAuto(targetTemp);
	targetTemp->SetupAttachment(GetRootComponent());
	targetTemp->SetRelativeLocation(FVector(1000, 0, 0));

	InteractionCollision->SetupAttachment(GetRootComponent());
	InteractionCollision->SetSphereRadius(88);

	GetMesh()->SetCollisionProfileName(FName("NoCollision"), false);
	GetCapsuleComponent()->SetCollisionProfileName(FName("Character"));
	InteractionCollision->SetCollisionProfileName(FName("Interaction"));

	MapAdd(isPressedSkill, ESkillType::Skill_1, false);
	MapAdd(isPressedSkill, ESkillType::Skill_2, false);
	MapAdd(isPressedSkill, ESkillType::Skill_3, false);
	MapAdd(isPressedSkill, ESkillType::Skill_4, false);

	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);

}

void ACBP_Character::BeginPlay()
{
	Super::BeginPlay();

	F_CharacterInfo characterInfo;

	if (character_InfoDataAsset != nullptr)
	{
		character_InfoDataAsset->GetCharacterInfo(characterName, characterInfo);
		maxHp = characterInfo.MaxHp;
		curHp = maxHp;
		max_Weapon_Inventory_Num = characterInfo.MaxWeaponInventoryNum;
		max_Item_Inventory_Num = characterInfo.MaxItemInventoryNum;
	}

	GetWorld()->GetTimerManager().SetTimer(hpTimerHandle, this, &ThisClass::UpdateHpValue, 0.1f, true);
	SetPauseTimer(hpTimerHandle);

	GetWorld()->GetTimerManager().SetTimer(CharacterSerchHandle, this, &ThisClass::SerchCloseTarget, 1.0f, true);
	SetPauseTimer(CharacterSerchHandle);

}

void ACBP_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (lifeTime > 0)
	{
		curLifeTime += DeltaTime;
		if (curLifeTime > lifeTime)
		{
			EndSpawn();
		}
	}


	if (is_Jump_Ready)
	{
		float TempPower = (cur_Jump_Power + (jump_Data.Charge * DeltaTime));
		cur_Jump_Power = UKismetMathLibrary::FClamp(TempPower, jump_Data.Min_Jump_Power, jump_Data.Max_Jump_Power);

		if (ACBP_PlayerController* controller = Cast<ACBP_PlayerController>(GetController()))
			controller->Player_Jump_Interface(cur_Jump_Power, jump_Data.Min_Jump_Power, jump_Data.Max_Jump_Power);
		
	}
	else
	{
		cur_Jump_Power = 0;
	}

	GuardGauge = UKismetMathLibrary::FClamp((GuardGauge + DeltaTime * GuardGaugeSpeed), 0, MaxGuardGauge);

	if (characterState == ECharacterState::Jump && GetCharacterMovement()->IsFalling() == false)
	{
		characterState = ECharacterState::Idle;
		bFallinged = false;
	}


	if (bFallinged == false && GetCharacterMovement()->IsFalling() == true)
	{
		if (characterState == ECharacterState::Idle)
		{
			characterState = ECharacterState::Jump;
		}

		bFallinged = true;
	}


}


/* =================================== ICBPI_Character ======================================*/
void ACBP_Character::ActionDodge()
{


}

void ACBP_Character::ActionDropping(bool & Success)
{
	UpdateInterface(EPlayerInterfaceUpdate::Weapon_Inventory);
}

void ACBP_Character::Skill(ESkillType InSkillType, bool isPressed)
{
	isPressedSkill[InSkillType] = isPressed;
	if (isPressed == false) return;

	bool canSkill = false;
	ThisClass::CanActionSkill(InSkillType, canSkill);
	if (!canSkill) return;
	
	
	if (auto* weapon = Cast<ACBP_MainWeapon>(main_Weapon))
	{
		// 무기에서 스킬이 가능한지를 따로 계산시킬 예정 연속스킬도 고려하기 위한 것
		F_WeaponSkillMontage skillMontage;

		weapon->GetSkillMontageData(characterName, InSkillType, skillMontage, canSkill);

		if (canSkill == false) return;

		characterState = ECharacterState::Skill;

		if (skillMontage.isMontageType)
		{
			PlayMontageCharacter(ThisClass, skillMontage.Montage, skillMontage.PlayRate, skillMontage.SectionName,
				"ReSetState",
				ThisClass::AddMontageEndedDelegate();
			);

		}
		else
		{
			// Idle를 SKillEnd에서 해줄 예정
			ACBP_Skill* temp;
			ThisClass::SkillSpawn(skillMontage.SkillClass, temp, InSkillType);

			temp->SetSpawn(nullptr);

			bool inSuccess = true;
			bool outSuccess = false;
			temp->Play(inSuccess, outSuccess);
		}

		// 스킬을 시전한 이후
		weapon->UsingSkill(InSkillType);
	}
}

void ACBP_Character::GunReLoad()
{
	ACBP_GunType_MainWeapon* gunWeapon = Cast<ACBP_GunType_MainWeapon>(main_Weapon);
	if (gunWeapon == nullptr) return;

	bool canReLoad = false;

	switch (characterState)
	{
	case ECharacterState::Idle:
	case ECharacterState::Attack:
	case ECharacterState::Jump:
	case ECharacterState::Skill:
		canReLoad = true;

	}

	if (canReLoad == false) return;

	if (character_MontageDataAsset == nullptr) return;

	F_BaseMontageData montageData;

	character_MontageDataAsset->GetCharacterMontage(ECharacterMontageName::GunReLoad, montageData);

	characterState = ECharacterState::ReLoad;

	PlayMontageCharacter(ThisClass, montageData.Montage, montageData.PlayRate, montageData.Section,
		"ReSetState",
		ThisClass::AddMontageEndedDelegate();
	);

	
//	bool Success = false;
//	gunWeapon->ReLoad(Success);
}

void ACBP_Character::JumpCharacter()
{
}

void ACBP_Character::Action()
{
	if (main_Weapon == nullptr) return;

	bool canAttack = false;
	ThisClass::CanAttack(canAttack);

	if (!canAttack)
	{
		bool same;
		ThisClass::IsCharacterState(ECharacterState::Attack, same);

		if (same && tempMontageData.NextCombo && enable_Next_Attack)
			cur_Attack_Is_End = false;

		return;
	}

	if (auto* weapon = Cast<ACBP_MainWeapon>(main_Weapon))
	{
		characterState = ECharacterState::Attack;

		weapon->GetMontageData(characterName, characterState, attack_Count, tempMontageData);

		PlayMontageCharacter(ThisClass,tempMontageData.Montage, tempMontageData.PlayRate, tempMontageData.Section,
			"Action",
			ThisClass::AddMontageEndedDelegate();
			ThisClass::AddMontageBlendOutDelegate();
		);

		attack_Count++;
	}

}

void ACBP_Character::EquipOrUnEquip()
{
	bool canArmming = false;

	ThisClass::CanArmming(canArmming);
	if (!canArmming) return;

	if (main_Weapon == nullptr)
		characterState = ECharacterState::Equip;
	else
	{
		if (main_Weapon == weapon_Inventory[cur_Using_Weapon_Num])
			characterState = ECharacterState::UnEquip;
		else
			characterState = ECharacterState::Equip;
	}

	bool same = false;
	ThisClass::IsCharacterState(ECharacterState::UnEquip, same);

	F_MontageData montageData;

	if (same)
	{
		if (auto* weapon = Cast<ACBP_MainWeapon>(main_Weapon))
		{
			weapon->GetMontageData(characterName, characterState, 0, montageData);

			PlayMontageCharacter(ThisClass,montageData.Montage, montageData.PlayRate, montageData.Section,
				"ReSetState",
				ThisClass::AddMontageEndedDelegate();
			);

		}
	}
	else
	{
		if (auto* weapon = Cast<ACBP_MainWeapon>(weapon_Inventory[cur_Using_Weapon_Num]))
		{
			weapon->GetMontageData(characterName, characterState, 0, montageData);

			PlayMontageCharacter(ThisClass,montageData.Montage, montageData.PlayRate, montageData.Section,
				"ReSetState",
				ThisClass::AddMontageEndedDelegate();
			);
		}
	}

}

void ACBP_Character::UsingItem(EItemName InUsingItemName, int InItemNum, bool & Success)
{
	EItemName usingItemName;

	if (InUsingItemName == EItemName::None)
		usingItemName = cur_Using_Item_Num;

	Success = false;
	if (itemInfoDataAsset == nullptr)
		return;

	if (Item_Inventory.Contains(usingItemName) == false) return;
	if (Item_Inventory[usingItemName] < InItemNum) return;


	F_ItemInfo itemInfo;
	itemInfoDataAsset->GetItemInfo(usingItemName, itemInfo);
	if (itemInfo.itemName == EItemName::None) return;

	Item_Inventory[usingItemName] -= InItemNum;

	F_Hp_Update_Value value;

	value.curUpdateTick = itemInfo.curUpdateTick;
	value.maxUpdateTick = itemInfo.maxUpdateTick;
	value.updateCount = itemInfo.updateCount;
	value.updateValue = itemInfo.updateValue;

	AddHpUpdate(value);

	ACBP_TextActor* textActor;
	FActorSpawnParameters param;

	SpawnActorUseClass(textActor, ACBP_TextActor::StaticClass(), param);
	textActor->SetActorLocation(GetActorLocation());

	textActor->SetTextFont(30);
	textActor->SetTextOutlineFont(0);
	textActor->SetTextBox(FString::FromInt(fabsf(value.updateValue * value.updateCount)), FVector(0,1,0));

	Success = true;

	UpdateInterface(EPlayerInterfaceUpdate::Item_Inventory);
}

void ACBP_Character::UsingItemNumIncreasing()
{
	switch (cur_Using_Item_Num)
	{
	case EItemName::None:
		cur_Using_Item_Num = EItemName::HP_Portion;
		break;
	case EItemName::HP_Portion:
		cur_Using_Item_Num = EItemName::Big_HP_Portion;
		break;
	case EItemName::Big_HP_Portion:
		cur_Using_Item_Num = EItemName::Max;
		break;
	case EItemName::Max:
		cur_Using_Item_Num = EItemName::None;
		break;
	}

	if (cur_Using_Item_Num == EItemName::Max)
		cur_Using_Item_Num = EItemName::None;

	if (cur_Using_Item_Num == EItemName::None)
		cur_Using_Item_Num = EItemName::HP_Portion;

	UpdateInterface(EPlayerInterfaceUpdate::Item_Inventory);
}

void ACBP_Character::ZoomCameraIn()
{
}

void ACBP_Character::ZoomCameraOut()
{
}

void ACBP_Character::WeaponSelect(int InInventoryNum)
{
	if (weapon_Inventory.Num() <= InInventoryNum) return;

	cur_Using_Weapon_Num = InInventoryNum;

	ThisClass::EquipOrUnEquip();
	ThisClass::UpdateInterface(EPlayerInterfaceUpdate::Weapon_Inventory);

}

void ACBP_Character::CharacterCrouch(bool InCrouch)
{
}

void ACBP_Character::CharacterJump(bool InIsJump)
{
	bool canJump = false;
	ThisClass::CanActionJump(canJump);
	if (!canJump)
	{
		cur_Jump_Power = 0;
		is_Jump_Ready = false;

		if (ACBP_PlayerController* controller = Cast<ACBP_PlayerController>(GetController()))
			controller->Player_Jump_Interface_newVisible(false);
		return;
	}

	if (InIsJump && !is_Jump_Ready)
	{
		is_Jump_Ready = true;
		if (ACBP_PlayerController* controller = Cast<ACBP_PlayerController>(GetController()))
		{
			controller->Player_Jump_Interface_newVisible(true);
		}
		return;
	}

	if (!(!InIsJump && is_Jump_Ready)) return;

	if (cur_Jump_Power == 0) return;

	GetCharacterMovement()->JumpZVelocity = cur_Jump_Power;
	is_Jump_Ready = false;
	characterState = ECharacterState::Jump;
	Cast<ACBP_Character>(this)->Jump();
	JumpStart();
	ZoomCameraOut();

	if (ACBP_PlayerController* controller = Cast<ACBP_PlayerController>(GetController()))
		controller->Player_Jump_Interface_newVisible(false);
}

void ACBP_Character::Speaker()
{
	if (ACBP_MainWeapon* mainWeapon = Cast<ACBP_MainWeapon>(main_Weapon))
	{
		if (mainWeapon->weaponName == EWeaponName::Rifle)
		{
			Action();
		}
	}
}

void ACBP_Character::ActionDown()
{
	if (character_MontageDataAsset == nullptr) return;

	if (characterState == ECharacterState::Dead) return;

	characterState = ECharacterState::Down;

	F_BaseMontageData montageData;

	character_MontageDataAsset->GetCharacterMontage(ECharacterMontageName::Down, montageData);

	PlayMontageCharacter(ThisClass, montageData.Montage, montageData.PlayRate, montageData.Section,
		"",);
}


void ACBP_Character::Landed(FHitResult const& HitResults)
{
	Super::Landed(HitResults);

	bFallinged = false;

	ActionRise();
}

void ACBP_Character::ActionRise()
{
	if (character_MontageDataAsset == nullptr) return;

	if (characterState == ECharacterState::Dead) return;
	if (characterState != ECharacterState::Down) return;

	characterState = ECharacterState::Rise;

	F_BaseMontageData montageData;

	character_MontageDataAsset->GetCharacterMontage(ECharacterMontageName::Rise, montageData);

	PlayMontageCharacter(ThisClass, montageData.Montage, montageData.PlayRate, montageData.Section,
		"ReSetState",
		ThisClass::AddMontageEndedDelegate();
	);

}

void ACBP_Character::ReSetState()
{
	characterState = ECharacterState::Idle;
	attack_Count = 0;
	cur_Attack_Is_End = true;
	bFallinged = false;
}

void ACBP_Character::AddDamage(AActor* WeaponActor, ECharacterDamagedType& damageType, F_Hp_Update_Value& resultDamage)
{
	damageType = ECharacterDamagedType::Failling;

	bool canDamaged = false;
	CanDamaged(canDamaged);
	if (canDamaged == false) return;

	bool isAttackActor = false;

	ACBP_Character* AttackCharacter = nullptr;
	F_Hp_Update_Value damage = F_Hp_Update_Value();
	EAttackType attackType = EAttackType::NormalAttack;
	EAttackHitType attackHitType = EAttackHitType::NoneHitAttack;
	EAttackPushType attackPushType = EAttackPushType::PushVector;
	EGuardSerchType guardSerchType = EGuardSerchType::Instigator;

	FVector PushVector = FVector(0, 0, 0);

	if (ICBPI_CanGetAttackDataObject* attackActor = Cast<ICBPI_CanGetAttackDataObject>(WeaponActor))
	{
		isAttackActor = true;
		attackActor->GetInstigatorcharacter(AttackCharacter);
		attackActor->GetFinalDamage(damage);

		attackActor->GetAttackType(attackType);
		attackActor->GetAttackHitType(attackHitType);

		attackActor->GetAttackPushType(attackPushType);
		attackActor->GetGuardSerchType(guardSerchType);

		attackActor->GetPushVector(PushVector);
	}

	if (isAttackActor == false) return;

//	if (ACBP_MainWeapon* mainWeapon = Cast<ACBP_MainWeapon>(WeaponActor))
//	{
//		AttackCharacter = Cast<ACBP_Character>(mainWeapon->GetInstigator());
//		mainWeapon->GetDamage(damage);
//		attackType = mainWeapon->attackType;
//		PushVector = mainWeapon->GetInstigator()->GetActorForwardVector();
//		attackHitType = mainWeapon->attackHitType;
//	}
//
//	if (ACBP_PairWeapon* pairWeapon = Cast<ACBP_PairWeapon>(WeaponActor))
//	{
//		AttackCharacter = Cast<ACBP_Character>(pairWeapon->GetInstigator());
//		pairWeapon->GetDamage(damage);
//		attackType = pairWeapon->attackType;
//		PushVector = pairWeapon->GetInstigator()->GetActorForwardVector();
//		attackHitType = pairWeapon->attackHitType;
//	}
//
//	if (ACBP_Skill* skill = Cast<ACBP_Skill>(WeaponActor))
//	{
//		AttackCharacter = Cast<ACBP_Character>(skill->GetInstigator());
//		damage = skill->damage;
//		attackType = skill->attackType;
//		PushVector = skill->pushVector;
//		attackHitType = skill->attackHitType;
//		attackPushType = skill->attackPushType;
//		guardSerchType = skill->guardSerchType;
//	}

	if (AttackCharacter != nullptr)
	{
		bool hostile = false;
		AttackCharacter->IsHostile(camp, hostile);
		if (hostile == false) return;
	}
	float damageValue = damage.updateValue;
	float correctValue = rand() % 10 - 5; // -5퍼에서 5퍼
	damageValue += damageValue * (correctValue / 100.0f);
	damage.updateValue = damageValue;

	resultDamage = damage;

	float temp;

	ZoomCameraOut();

	switch (attackPushType)
	{
	case EAttackPushType::WeaponLocation:
		(GetActorLocation() - WeaponActor->GetActorLocation()).ToDirectionAndLength(PushVector, temp);
		break;
	case EAttackPushType::InstigatorLocation:
		(GetActorLocation() - WeaponActor->GetInstigator()->GetActorLocation()).ToDirectionAndLength(PushVector, temp);
		break;
	case EAttackPushType::NonePush:
		PushVector = FVector(0, 0, 0);
		break;
	}

	bool GuardSuccess = false;

	if (isGuard)
	{
		TArray<FHitResult> results;

		FVector traceEnd = traceEnd = WeaponActor->GetActorLocation();
		switch (guardSerchType)
		{
		case EGuardSerchType::Owner:
			if (WeaponActor->GetOwner() != nullptr)
				traceEnd = WeaponActor->GetOwner()->GetActorLocation();
			break;
		case EGuardSerchType::Instigator:
			if(WeaponActor->GetInstigator() != nullptr)
				traceEnd = WeaponActor->GetInstigator()->GetActorLocation();
			break;
		}

		UKismetSystemLibrary::LineTraceMulti(
			GetWorld(),
			GetActorLocation(),
			traceEnd,
			ETraceTypeQuery::TraceTypeQuery5,
			false,
			{ this },
			EDrawDebugTrace::Type::None,
			results,
			true
		);

		for (FHitResult result : results)
		{
			if (result.GetActor()->GetInstigator() == this)
			{
				GuardSuccess = true;
				break;
			}
		}

		if (GuardSuccess == false)
		{
			ThisClass::AddHpUpdate(damage);
		}

		float GuageDeleteValue = damage.updateValue * damage.updateCount;

		switch (attackType)
		{
		case EAttackType::NormalAttack:
			break;
		case EAttackType::HeavyAttack:
			GuageDeleteValue *= 5;
			break;
		case EAttackType::LightAttack:
			GuageDeleteValue *= 0.1f;
			break;
		}

		GuardGauge -= GuageDeleteValue;
	}
	else
	{
		ThisClass::AddHpUpdate(damage);
	}

	// State조정 부분 NoneAttack이면 데미지만 줄 것
	if (attackHitType != EAttackHitType::NoneHitAttack)
	{
		if (characterState == ECharacterState::Damaged || characterState == ECharacterState::Down)
		{
			if (GuardSuccess == false)
			{
				characterState = ECharacterState::Down;
			}
			else
			{
				characterState = ECharacterState::Damaged;
			}
		}
		else
		{
			if (attackHitType == EAttackHitType::DownAttack)
			{
				characterState = ECharacterState::Down;
			}

			if (attackHitType == EAttackHitType::HitAttack)
				characterState = ECharacterState::Damaged;
		}


		// 몽타쥬 부분
		if (characterState == ECharacterState::Damaged)
		{
			F_BaseMontageData montageData;
			ECharacterMontageName montageName;

			if (GuardSuccess == true)
			{
				if (GuardGauge <= 0)
				{
					montageName = ECharacterMontageName::GuardBreak;
					isGuard = false;
				}
				else
					montageName = ECharacterMontageName::GuardSuccess;
			}
			else
			{
				montageName = ECharacterMontageName::Damaged;
			}

			character_MontageDataAsset->GetCharacterMontage(montageName, montageData);

			PlayMontageCharacter(ThisClass, montageData.Montage, montageData.PlayRate, montageData.Section,
				"ReSetState",
				ThisClass::AddMontageEndedDelegate();
			);


		}
		
		if (characterState == ECharacterState::Down)
		{
			ActionDown();

			AddActorWorldOffset(FVector(0, 0, 50), true);
		}
	}

	// 밀리는것 
	if (attackPushType != EAttackPushType::NonePush)
	{
		float lenght;
		PushVector.Z = 0;

		PushVector.ToDirectionAndLength(PushVector, lenght);

		GetCharacterMovement()->AddImpulse(PushVector * 100);

		FRotator newRotator;

		if (WeaponActor->GetInstigator() == nullptr)
		{
			newRotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), WeaponActor->GetActorLocation());
		}
		else
		{
			newRotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), WeaponActor->GetInstigator()->GetActorLocation());
		}

		SetActorRotation(FRotator(0, newRotator.Yaw, 0));
	}

	damageType = ECharacterDamagedType::NormalHit;

	if(GuardSuccess)
		damageType = ECharacterDamagedType::Guard;

	if (WeaponActor->GetInstigator() != nullptr)
	{
		targetCandidate.Add(WeaponActor->GetInstigator());
		SetUnPauseTimer(CharacterSerchHandle);
	}
	
}

void ACBP_Character::UpdateHpWidget()
{

}

void ACBP_Character::CheckTarget()
{

}

void ACBP_Character::UpdateInterface(EPlayerInterfaceUpdate updateType)
{

}

void ACBP_Character::Interaction()
{

}

void ACBP_Character::InteractionSelect(float Value)
{

}

void ACBP_Character::SetDie()
{
	characterState = ECharacterState::Dead;
	SetPauseTimer(hpTimerHandle);

	if (character_MontageDataAsset == nullptr) return;

	GetCapsuleComponent()->SetCollisionProfileName(FName("DeadCharacter"));
	InteractionCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	F_BaseMontageData montageData;
	character_MontageDataAsset->GetCharacterMontage(ECharacterMontageName::Dead, montageData);

	PlayMontageCharacter(ThisClass, montageData.Montage, montageData.PlayRate, montageData.Section,
		"",
		ThisClass::AddMontageEndedDelegate();
	);

//	KismetDelay(TEXT("DestroyThisCharacter"), this, 5);

}

void ACBP_Character::SetSpawnLifeTime(float time)
{
//	KismetDelay(TEXT("EndSpawn"), this, time);

	lifeTime = time;
	curLifeTime = 0;
}

void ACBP_Character::EndSpawn()
{
	F_Hp_Update_Value data;
	data.updateValue = FLT_MAX;
	data.updateCount = INT_MAX;

	AddHpUpdate(data);
}


void ACBP_Character::SetSpawnerActor(AActor* InSpawnedActor)
{
	SpawnedActors.Add(InSpawnedActor);
}

void ACBP_Character::SetDeleteSpawnedActor(AActor* InDeleteSpawnedActor)
{
	if (SpawnedActors.Contains(InDeleteSpawnedActor) == true)
		SpawnedActors.Remove(InDeleteSpawnedActor);

}
/*=============================== ICBPI_Character ==================================*/
/* =================================================================================*/

//// Called to bind functionality to input
//void ACBP_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}

