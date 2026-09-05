// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Struct/SWeapon.h"
#include "C_WeaponCoolTimeDataAsset.generated.h"


USTRUCT(BlueprintType)
struct F_WeaponSkillCoolTImeDataAssrtData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TArray<F_WeaponSkillCoolTIme> skillCoolTime;
};

UCLASS()
class CPROJECT_API UC_WeaponCoolTimeDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
		void GetWeaponCoolTime(ECharacterName const characterName, TMap<ESkillType, F_WeaponSkillCoolTIme>& result);

public:

	UPROPERTY(EditAnywhere) TMap<ECharacterName, F_WeaponSkillCoolTImeDataAssrtData> coolTimeData;

};
