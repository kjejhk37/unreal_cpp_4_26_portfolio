#pragma once

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	None,
	Skill_1,
	Skill_2,
	Skill_3,
	Skill_4,
	Max
};


UENUM(BlueprintType)
enum class EWeaponName : uint8
{
	None,
	DualBlade ,
	TwinSword,
	Rifle,
	Bow,
	Warior,
	Staff,
	LongSword,
	Max
};

UENUM(BlueprintType)
enum class EHomingSkillType : uint8
{
	targetHoming,
	characterTemptargetHoming,
	endPosHoming,
	InstigatorHomming
};

UENUM(BlueprintType)
enum class EAttackType : uint8
{
	NormalAttack,
	HeavyAttack,
	LightAttack
};

UENUM(BlueprintType)
enum class EAttackHitType : uint8
{
	HitAttack,
	DownAttack,
	NoneHitAttack
};

UENUM(BlueprintType)
enum class EAttackPushType : uint8
{
	PushVector,
	WeaponLocation,
	InstigatorLocation,
	NonePush
};

