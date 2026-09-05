#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/EngineTypes.h"
#include "Enums/ECharacter.h"
#include "SCharacter.generated.h"

// struct를 만들때는 S말고 F로 시작해야 함 이유는 몰름

USTRUCT(BlueprintType)
struct F_CharacterInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) ECharacterName characterName;
	UPROPERTY(EditAnywhere) float MaxHp;
	UPROPERTY(EditAnywhere) int MaxWeaponInventoryNum;
	UPROPERTY(EditAnywhere) int MaxItemInventoryNum;
};

USTRUCT(BlueprintType)
struct F_Hp_Update_Value
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) float updateValue = 0;
	UPROPERTY(EditAnywhere) int updateCount = 1;
	UPROPERTY(EditAnywhere) int curUpdateTick = 0;
	UPROPERTY(EditAnywhere) int maxUpdateTick = 0;
};

USTRUCT(BlueprintType)
struct F_JumpData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) ECharacterName characterName;
	UPROPERTY(EditAnywhere) float Min_Jump_Power;
	UPROPERTY(EditAnywhere) float Max_Jump_Power;
	UPROPERTY(EditAnywhere) float Charge;
};

USTRUCT(BlueprintType)
struct F_MontageData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) ECharacterState CharacterState;
	UPROPERTY(EditAnywhere) int Combo;
	UPROPERTY(EditAnywhere) UAnimMontage* Montage;
	UPROPERTY(EditAnywhere) float PlayRate;
	UPROPERTY(EditAnywhere) FName Section;
	UPROPERTY(EditAnywhere) bool NextCombo;
};

USTRUCT(BlueprintType)
struct F_BaseMontageData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) ECharacterMontageName CharacterMontageName;
	UPROPERTY(EditAnywhere) UAnimMontage* Montage = nullptr;
	UPROPERTY(EditAnywhere) float PlayRate = 1;
	UPROPERTY(EditAnywhere) FName Section;
};