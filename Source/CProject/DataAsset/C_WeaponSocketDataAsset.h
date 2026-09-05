// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Enums/ECharacter.h"
#include "Struct/SWeapon.h"
#include "C_WeaponSocketDataAsset.generated.h"

UCLASS()
class CPROJECT_API UC_WeaponSocketDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable) 
		void GetWeaponSocket(bool const isPairWeapon, ECharacterName const characterName, F_WeaponSocket& result);


public:
	UPROPERTY(EditAnywhere) TArray<F_WeaponSocket> SocketDatas;
	UPROPERTY(EditAnywhere) TArray<F_WeaponSocket> PairWeaponSocketDatas;

};
