// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Animation/CABP_Character.h"
#include "ACBP_AICharacter.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API UACBP_AICharacter : public UCABP_Character
{
	GENERATED_BODY()
	
public:
	UACBP_AICharacter();

	virtual void NativeUpdateAnimation(float const DeltaSeconds) override;

	UFUNCTION() void SetEndSpawn();

protected:
	UPROPERTY(BlueprintReadOnly)	bool EndSpawn = false;
};
