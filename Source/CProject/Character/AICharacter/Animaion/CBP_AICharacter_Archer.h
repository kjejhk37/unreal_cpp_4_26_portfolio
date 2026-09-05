// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AICharacter/Animaion/ACBP_AICharacter.h"
#include "CBP_AICharacter_Archer.generated.h"


UCLASS()
class CPROJECT_API UCBP_AICharacter_Archer : public UACBP_AICharacter
{
	GENERATED_BODY()

public:
	UCBP_AICharacter_Archer();

	virtual void NativeUpdateAnimation(float const DeltaSeconds) override;

	
};
