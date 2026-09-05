// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "Character/CBP_Character.h"

#include "CBPI_CanGetAttackDataObject.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCBPI_CanGetAttackDataObject : public UInterface
{
	GENERATED_BODY()
};

class CPROJECT_API ICBPI_CanGetAttackDataObject
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void GetInstigatorcharacter(ACBP_Character*& outCharacter) PURE_VIRTUAL(ICBPI_CanGetAttackDataObject::GetInstigatorcharacter, return;);
	virtual void GetFinalDamage(F_Hp_Update_Value& outDamage) PURE_VIRTUAL(ICBPI_CanGetAttackDataObject::GetDamage, return;);

	virtual void GetAttackType(EAttackType& outAttackType) PURE_VIRTUAL(ICBPI_CanGetAttackDataObject::GetAttackType, return;);
	virtual void GetAttackHitType(EAttackHitType& outAttackHitType) PURE_VIRTUAL(ICBPI_CanGetAttackDataObject::GetAttackHitType, return;);

	virtual void GetPushVector(FVector& outPushVector) PURE_VIRTUAL(ICBPI_CanGetAttackDataObject::GetPushVector, return;);
	virtual void GetAttackPushType(EAttackPushType& outAttackPushType) PURE_VIRTUAL(ICBPI_CanGetAttackDataObject::GetAttackPushType, return;);

	virtual void GetGuardSerchType(EGuardSerchType& outGuardSerchType) PURE_VIRTUAL(ICBPI_CanGetAttackDataObject::GetGuardSerchType, return;);

	virtual void GetCamp(ECamp& outCamp) PURE_VIRTUAL(ICBPI_CanGetAttackDataObject::GetCamp, return;);

	virtual void WorkAttackTerrain() PURE_VIRTUAL(ICBPI_CanGetAttackDataObject::WorkAttackTerrain, return;);


	/*
		AttackCharacter = Cast<ACBP_Character>(skill->GetInstigator());
		damage = skill->damage;
		attackType = skill->attackType;
		PushVector = skill->pushVector;
		attackHitType = skill->attackHitType;
		attackPushType = skill->attackPushType;
		guardSerchType = skill->guardSerchType;
	*/

};
