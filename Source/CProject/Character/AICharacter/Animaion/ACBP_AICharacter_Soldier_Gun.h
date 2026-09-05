// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AICharacter/Animaion/ACBP_AICharacter.h"
#include "ACBP_AICharacter_Soldier_Gun.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API UACBP_AICharacter_Soldier_Gun : public UACBP_AICharacter
{
	GENERATED_BODY()
public:
	UACBP_AICharacter_Soldier_Gun();

	virtual void NativeUpdateAnimation(float const DeltaSeconds) override;

};
