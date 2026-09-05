// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Struct/SWeapon.h"
#include "Struct/SCharacter.h"

#include "C_MontageDataAsset.generated.h"


UCLASS()
class CPROJECT_API UC_MontageDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable) void GetSkillMontageData(ESkillType const skillType, F_WeaponSkillMontage& result);
	UFUNCTION(BlueprintCallable) void GetMontageData(ECharacterState const state,int const combo, F_MontageData& result);

public:
	UPROPERTY(EditAnywhere) TArray<F_WeaponSkillMontage> SkillMontageDatas;
	UPROPERTY(EditAnywhere) TArray<F_MontageData> MontageDatas;

};
