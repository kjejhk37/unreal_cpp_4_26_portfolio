// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Struct/SCharacter.h"
#include "C_CharacterInfoDataAsset.generated.h"

UCLASS()
class CPROJECT_API UC_CharacterInfoDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable) void GetCharacterInfo(ECharacterName characterName, F_CharacterInfo& result);

public:
	UPROPERTY(EditAnywhere)	// EditAnyWhere¸¸ µÊ
		TArray<F_CharacterInfo> characterInfoDatas;


};
