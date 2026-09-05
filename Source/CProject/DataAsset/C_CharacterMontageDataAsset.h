// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Struct/SCharacter.h"
#include "C_CharacterMontageDataAsset.generated.h"


UCLASS()
class CPROJECT_API UC_CharacterMontageDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable) void GetCharacterMontage(ECharacterMontageName characterMontageName, F_BaseMontageData& result);

public:
	UPROPERTY(EditAnywhere)	// EditAnyWhere¸¸ µÊ
		TArray<F_BaseMontageData> characterMontageDatas;

	
};
