#pragma once

UENUM(BlueprintType)
enum class ECharacterName : uint8
{
	None,
	Player,
	ArcherSkel,
	FootmanSkel,
	SorcererSkel,
	WarlordSkel,
	SoldierGun,
	Max
};

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Idle,
	Attack,
	UsingItem,
	UnEquip,
	Equip,
	Dodge,
	ReLoad,
	Jump,
	Skill,
	Damaged,
	Down,
	Rise,
	Dead,
	Spawn
};

UENUM(BlueprintType)
enum class ECharacterMontageName : uint8
{
	Down,
	Rise,
	Damaged,
	GuardSuccess,
	GuardBreak,
	Dodge,
	Spawn,
	GunReLoad,
	JumpStart,
	JumpEnd,
	Dead
};

UENUM(BlueprintType)
enum class EPlayerInterfaceUpdate : uint8
{
	HP_Gauge,
	Guard_Gauge,
	Skill,
	Weapon_Inventory,
	Item_Inventory
};

UENUM(BlueprintType)
enum class EGuardSerchType : uint8
{
	Actor,
	Owner,
	Instigator
};


UENUM(BlueprintType)
enum class ECharacterDamagedType : uint8
{
	NormalHit,
	Critical,
	Guard,
	Failling
};
