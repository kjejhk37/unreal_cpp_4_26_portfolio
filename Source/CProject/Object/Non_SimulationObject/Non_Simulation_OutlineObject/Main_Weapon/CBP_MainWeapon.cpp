// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/Main_Weapon/CBP_MainWeapon.h"
#include "Character/CBP_Character.h"
#include "Object/SimulationObject/Interaction_Object/Case/CBP_WeaponCase.h"

#include "Macro/MyMacro.h"

#include "Logger/Logger.h"

#include "UI/CBP_TextActor.h"


ACBP_MainWeapon::ACBP_MainWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	F_WeaponSkillCoolTIme temp;
}

void ACBP_MainWeapon::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);
}

void ACBP_MainWeapon::Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType)
{
	Super::Set_NonSimul_ComponentsBase(newMeshType, newInteractionType);
}

void ACBP_MainWeapon::BeginPlay()
{
	Super::BeginPlay();

	SetScale(main_Weapon_Scale);
}

void ACBP_MainWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (TPair<ESkillType, F_WeaponSkillCoolTIme>& data : skillCoolTimes)
	{
		if (data.Value.skillStack == data.Value.curSkillStack)
		{
			continue;
		}

		data.Value.curCoolTime += DeltaTime;

		if (data.Value.curCoolTime > data.Value.CoolTime)
		{
			if (data.Value.curSkillStack < data.Value.skillStack)
			{
				data.Value.curSkillStack++;
			}

			data.Value.curCoolTime = 0;
		}
	}
}

void ACBP_MainWeapon::Activate(bool InSuccess, bool & OutSuccess)
{
	OutSuccess = InSuccess;
}

void ACBP_MainWeapon::DeActivate(bool InSuccess, bool & OutSuccess)
{
	OutSuccess = InSuccess;
}

void ACBP_MainWeapon::DroppingMainWeapon(bool & Success)
{
	Success = false;

	if (weaponCase == nullptr) return;

	FVector newLocation = GetInstigator()->GetActorLocation();
	FVector velocity = GetInstigator()->GetActorForwardVector();

	SetAttachRules(rule);
	this->AttachToComponent(weaponCase->mainWeaponSocket, rule);

	SetInstigator(nullptr);
	SetOwner(nullptr);

	if (pairWeapon != nullptr)
	{
		bool InSuccess = false;
		pairWeapon->DroppingPairWeapon(this, InSuccess);

		if (InSuccess == false) return;
	}

	SetScale(main_Weapon_Scale);
	SetVisible(true);
	SetHiddenOutline(false);

	weaponCase->SetDropping(newLocation, velocity,500);
	Success = true;
}

void ACBP_MainWeapon::PickUpWeapon(AActor * actor, bool & Success)
{
	ACBP_Character* character = Cast<ACBP_Character>(actor);
	Success = false;

	if (character == nullptr) return;

	SetInstigator(character);
	SetOwner(character);

	if (pairWeapon != nullptr)
	{
		pairWeapon->SetInstigator(character);
		pairWeapon->SetOwner(character);

		bool Success = false;
		pairWeapon->PickUpWeapon(character, Success);
	}

	SetSocket();
	SetSkillCoolTime();

	SetEquip(actor, false);

	SetHiddenOutline(true);


	Success = true;
}

void ACBP_MainWeapon::SetEquip(AActor* actor,bool const Equip)
{
	ACBP_Character* character = Cast<ACBP_Character>(actor);
	if (character == nullptr) return;

	SetScale(main_Weapon_Scale);
	character->AttachActorToCharacter(this, Equip);
	SetVisible(Equip);
	
	UpdateInterface(Equip);
}

void ACBP_MainWeapon::UpdateInterface(bool Equip)
{

}

void ACBP_MainWeapon::GetMontageData(ECharacterName const characterName, ECharacterState const state, int const Combo, F_MontageData & result)
{
	if(IsValid(montageDataAssets[characterName]))
		montageDataAssets[characterName]->GetMontageData(state, Combo, result);
}


void ACBP_MainWeapon::GetSkillMontageData(ECharacterName const characterName, ESkillType const skillType, F_WeaponSkillMontage & result, bool& canSkill)
{
	F_WeaponSkillCoolTIme data = skillCoolTimes[skillType];

	canSkill = false;
	if (data.curSkillStack == 0) return;

	canSkill = true;
	if (IsValid(montageDataAssets[characterName]))
		montageDataAssets[characterName]->GetSkillMontageData(skillType, result);

}

void ACBP_MainWeapon::SetSkillCoolTime()
{
	ACBP_Character* character = Cast<ACBP_Character>(GetInstigator());
	if (character == nullptr) return;
	if (coolTimeDataAsset == nullptr) return;

	coolTimeDataAsset->GetWeaponCoolTime(character->characterName, skillCoolTimes);
}

void ACBP_MainWeapon::UsingSkill(ESkillType skillType)
{
	F_WeaponSkillCoolTIme& data = skillCoolTimes[skillType];
	data.curSkillStack--;
}

void ACBP_MainWeapon::SetSocket()
{
	ACBP_Character* character = Cast<ACBP_Character>(GetInstigator());
	if (character == nullptr) return;

	if (socketDataAsset == nullptr) return;

	F_WeaponSocket socketData;

	socketDataAsset->GetWeaponSocket(false, character->characterName, socketData);

	equip_Socket = socketData.EquipSocket;
	unEquip_Socket = socketData.UnEquipSocket;

	if (pairWeapon != nullptr)
	{
		socketDataAsset->GetWeaponSocket(true, character->characterName, socketData);

		pairWeapon->equip_Socket = socketData.EquipSocket;
		pairWeapon->unEquip_Socket = socketData.UnEquipSocket;
	}
}

void ACBP_MainWeapon::GetDamage(F_Hp_Update_Value & weaponDamage)
{
	weaponDamage = damage;
}

void ACBP_MainWeapon::SetDamage(F_Hp_Update_Value const weaponDamage)
{
	damage = weaponDamage;
}

void ACBP_MainWeapon::GetSkillCoolTime(ESkillType const skillType, F_WeaponSkillCoolTIme& result)
{
	result = skillCoolTimes[skillType];
}

void ACBP_MainWeapon::SpawnTextActor(FString string, FVector Location, FVector fontColor, float fontSize, float outlineFontSize)
{
	ACBP_TextActor* textActor;
	FActorSpawnParameters param;

	SpawnActorUseClass(textActor, ACBP_TextActor::StaticClass(), param);
	textActor->SetActorLocation(Location);

	textActor->SetTextFont(fontSize);
	textActor->SetTextOutlineFont(outlineFontSize);
	textActor->SetTextBox(string, fontColor);
}

void ACBP_MainWeapon::GetInstigatorcharacter(ACBP_Character*& outCharacter) { outCharacter = Cast<ACBP_Character>(GetInstigator()); }
void ACBP_MainWeapon::GetFinalDamage(F_Hp_Update_Value& outDamage) { GetDamage(outDamage); }
void ACBP_MainWeapon::GetAttackType(EAttackType& outAttackType) { outAttackType = attackType; }
void ACBP_MainWeapon::GetAttackHitType(EAttackHitType& outAttackHitType) { outAttackHitType = attackHitType; }
void ACBP_MainWeapon::GetPushVector(FVector& outPushVector) { if(GetInstigator() != nullptr) outPushVector = GetInstigator()->GetActorForwardVector(); }
void ACBP_MainWeapon::GetAttackPushType(EAttackPushType& outAttackPushType) { outAttackPushType = EAttackPushType::PushVector; }
void ACBP_MainWeapon::GetGuardSerchType(EGuardSerchType& outGuardSerchType) { outGuardSerchType = EGuardSerchType::Instigator; }
void ACBP_MainWeapon::GetCamp(ECamp& outCamp) { if (ACBP_Character* character = Cast<ACBP_Character>(GetInstigator())) { outCamp = character->camp; } else { outCamp = ECamp::Neutrality; } }