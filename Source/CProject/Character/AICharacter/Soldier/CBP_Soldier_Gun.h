// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AICharacter/CBP_AICharacter.h"
#include "CBP_Soldier_Gun.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API ACBP_Soldier_Gun : public ACBP_AICharacter
{
	GENERATED_BODY()
public:
	ACBP_Soldier_Gun();

	void SetDie() override;

	void Action() override;
	void EquipOrUnEquip() override;
	void ActionDropping(bool& Success) override;
protected:
	UFUNCTION() void SoldierOnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	
	UPROPERTY(EditDefaultsOnly) class UParticleSystem* EndParticle;

};
