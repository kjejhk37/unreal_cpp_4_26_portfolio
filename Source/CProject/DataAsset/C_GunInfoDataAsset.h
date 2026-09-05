// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Struct/SWeapon.h"
#include "C_GunInfoDataAsset.generated.h"

UCLASS()
class CPROJECT_API UC_GunInfoDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable) void GetGunInfo(EWeaponName const weaponName, F_GunTypeInfo& result);

public:
	UPROPERTY(EditAnywhere) TArray<F_GunTypeInfo> gunInfoDatas;

};
