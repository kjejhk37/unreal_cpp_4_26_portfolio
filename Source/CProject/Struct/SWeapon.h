#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/EngineTypes.h"
#include "Enums/EWeapon.h"
#include "Enums/ECharacter.h"
#include "Skill/CBP_Skill.h"
#include "Object/SimulationObject/Non_Interaction_Object/CBP_Non_InteractionObject.h"
#include "SWeapon.generated.h"

// struct를 만들때는 S말고 F로 시작해야 함 이유는 몰름

USTRUCT(BlueprintType)
struct F_WeaponSkillMontage
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) ESkillType SkillType;
	UPROPERTY(EditAnywhere) bool isMontageType;

	UPROPERTY(EditAnywhere) UAnimMontage* Montage;
	UPROPERTY(EditAnywhere) float PlayRate;
	UPROPERTY(EditAnywhere) FName SectionName;
	
	UPROPERTY(EditAnywhere) TSubclassOf<ACBP_Skill> SkillClass;
};

USTRUCT(BlueprintType)
struct F_WeaponSkillCoolTIme
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) ESkillType skillType;

	UPROPERTY(EditAnywhere) float CoolTime = 0;
	UPROPERTY(EditAnywhere) float curCoolTime = 0;

	UPROPERTY(EditAnywhere) int skillStack = 0;
	UPROPERTY(EditAnywhere) int curSkillStack = 0;
};


USTRUCT(BlueprintType)
struct F_WeaponSocket
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) ECharacterName CharacterName;

	UPROPERTY(EditAnywhere) FName EquipSocket;
	UPROPERTY(EditAnywhere) FName UnEquipSocket;
};


USTRUCT(BlueprintType)
struct F_GunTypeInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) EWeaponName WeapoName;

	UPROPERTY(EditAnywhere) TSubclassOf<ACBP_Non_InteractionObject> FallingBullet;
	UPROPERTY(EditAnywhere) TSubclassOf<ACBP_Non_InteractionObject> FallingMagazine;

	UPROPERTY(EditAnywhere) FName MagazineSocket;
	UPROPERTY(EditAnywhere) FName BulletSocket;
	UPROPERTY(EditAnywhere) FName ShotSocket;

	UPROPERTY(EditAnywhere) float AttackLength;
	UPROPERTY(EditAnywhere) int RemainBullet;
	UPROPERTY(EditAnywhere) int MaxBullet;

};

USTRUCT(BlueprintType)
struct F_ParticleActorData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TSubclassOf<AActor> particleClass;

	UPROPERTY(EditAnywhere) float StartDelayTime;
	UPROPERTY(EditAnywhere) float EndDelayTime;

};