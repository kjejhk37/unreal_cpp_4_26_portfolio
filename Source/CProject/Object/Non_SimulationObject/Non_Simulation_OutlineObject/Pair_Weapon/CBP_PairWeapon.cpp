// Fill out your copyright notice in the Description page of Project Settings.


#include "CBP_PairWeapon.h"
#include "Character/CBP_Character.h"

#include "Macro/IncludeMacro.h"
#include "Macro/MyMacro.h"

#include "Logger/Logger.h"

#include "UI/CBP_TextActor.h"

#include MainWeaponPath

ACBP_PairWeapon::ACBP_PairWeapon()
{

}
	
void ACBP_PairWeapon::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ACBP_PairWeapon::BeginPlay()
{
	Super::BeginPlay();


	SetScale(pair_Weapon_Scale);
}

void ACBP_PairWeapon::Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType)
{
	Super::Set_NonSimul_ComponentsBase(newMeshType, newInteractionType);
}

/* ================================ interface ======================================*/
void ACBP_PairWeapon::Activate(bool InSuccess, bool& OutSuccess)
{

}

void ACBP_PairWeapon::DeActivate(bool InSuccess, bool& OutSuccess)
{

}

/*===================================================================================*/
void ACBP_PairWeapon::DroppingPairWeapon(AActor * mainWeapon, bool & Success)
{
	ACBP_MainWeapon* main_Weapon = Cast<ACBP_MainWeapon>(mainWeapon);

	if (main_Weapon == nullptr)
	{
		Success = false;
		return;
	}

	FAttachmentTransformRules const Rule(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(main_Weapon->weaponCase->pairWeaponSocket, Rule);

	SetInstigator(nullptr);
	SetOwner(nullptr);
	SetScale(pair_Weapon_Scale);
	SetVisible(true);
	SetHiddenOutline(false);
	Success = true;

}

void ACBP_PairWeapon::PickUpWeapon(AActor * actor, bool & Success)
{
	ACBP_Character* character = Cast<ACBP_Character>(actor);
	if (character == nullptr)
	{
		Success = false;
		return;
	}

	SetInstigator(character);

	ThisClass::SetEquip(false);
	ThisClass::SetScale(pair_Weapon_Scale);
	SetHiddenOutline(true);

	Success = true;
}

void ACBP_PairWeapon::SetEquip(bool const Equip)
{
	ACBP_Character* character = Cast<ACBP_Character>(GetInstigator());
	if (character == nullptr) return;

	SetScale(pair_Weapon_Scale);
	character->AttachActorToCharacter(this, Equip);
	SetVisible(Equip);

}

void ACBP_PairWeapon::GetDamage(F_Hp_Update_Value & outDamage)
{
	outDamage = damage;
}

void ACBP_PairWeapon::SetDamage(F_Hp_Update_Value const inDamage)
{
	damage = inDamage;
}

void ACBP_PairWeapon::SpawnTextActor(FString string, FVector Location, FVector fontColor, float fontSize, float outlineFontSize)
{
	ACBP_TextActor* textActor;
	FActorSpawnParameters param;

	SpawnActorUseClass(textActor, ACBP_TextActor::StaticClass(), param);
	textActor->SetActorLocation(Location);

	textActor->SetTextFont(fontSize);
	textActor->SetTextOutlineFont(outlineFontSize);
	textActor->SetTextBox(string, fontColor);
}

void ACBP_PairWeapon::GetInstigatorcharacter(ACBP_Character*& outCharacter) { outCharacter = Cast<ACBP_Character>(GetInstigator()); }
void ACBP_PairWeapon::GetFinalDamage(F_Hp_Update_Value& outDamage) { GetDamage(outDamage); }
void ACBP_PairWeapon::GetAttackType(EAttackType& outAttackType) { outAttackType = attackType; }
void ACBP_PairWeapon::GetAttackHitType(EAttackHitType& outAttackHitType) { outAttackHitType = attackHitType; }
void ACBP_PairWeapon::GetPushVector(FVector& outPushVector) { if (GetInstigator() != nullptr) outPushVector = GetInstigator()->GetActorForwardVector(); }
void ACBP_PairWeapon::GetAttackPushType(EAttackPushType& outAttackPushType) { outAttackPushType = EAttackPushType::PushVector; }
void ACBP_PairWeapon::GetGuardSerchType(EGuardSerchType& outGuardSerchType) { outGuardSerchType = EGuardSerchType::Instigator; }
void ACBP_PairWeapon::GetCamp(ECamp& outCamp) { if (ACBP_Character* character = Cast<ACBP_Character>(GetInstigator())) { outCamp = character->camp; } else { outCamp = ECamp::Neutrality; } }