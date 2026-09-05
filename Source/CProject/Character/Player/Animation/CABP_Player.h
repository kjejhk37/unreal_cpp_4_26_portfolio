// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Animation/CABP_Character.h"
#include "Enums/ECharacter.h"
#include "Enums/EWeapon.h"
#include "CABP_Player.generated.h"

UCLASS()
class CPROJECT_API UCABP_Player : public UCABP_Character
{
	GENERATED_BODY()

public:
	UCABP_Player();

	virtual void NativeUpdateAnimation(float const DeltaSeconds) override;

	void SetZoom(bool InisZoom);

protected:
	UPROPERTY(BlueprintReadOnly)	ECharacterState characterState;
	UPROPERTY(BlueprintReadOnly)	EWeaponName weaponName;

	UPROPERTY(BlueprintReadOnly)	bool isZoom;


private:
	void UpdateCharacterState();
	void UpdateAim();

	void StartDodge();
	void StartJump();
	void EndJump();

};
