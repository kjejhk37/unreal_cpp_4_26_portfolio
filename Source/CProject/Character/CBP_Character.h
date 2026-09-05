// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Struct/SCharacter.h"
#include "Enums/ECamps.h"
#include "Enums/EWeapon.h"
#include "DataAsset/C_CharacterInfoDataAsset.h"
#include "DataAsset/C_CharacterMontageDataAsset.h"
#include "DataAsset/C_ItemInfoDataAsset.h"

#include "Interface/CBPI_Character.h"
#include "Interface/CBPI_SpawnerActor.h"
#include "CBP_Character.generated.h"


UCLASS()
class CPROJECT_API ACBP_Character : public ACharacter , public ICBPI_Character , public ICBPI_SpawnerActor
{
	GENERATED_BODY()

public:
	ACBP_Character();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public: 
	/*===========================ICBPI_Character =================================*/
	// Action
	void ActionDodge() override;
	void ActionDropping(bool& Success) override;
	void GunReLoad() override;
	void JumpCharacter() override;
	void Action() override;
	void EquipOrUnEquip() override;

	//Skill
	void Skill(ESkillType InSkillType, bool isPressed) override;

	// Item
	void UsingItem(EItemName InUsingItemName, int InItemNum, bool& Success) override;
	void UsingItemNumIncreasing() override;

	// Zoom
	void ZoomCameraIn()override;
	void ZoomCameraOut() override;

	// WeaponSelect
	void WeaponSelect(int InInventoryNum) override;

	// MoveEvent
	void CharacterCrouch(bool InCrouch)override;
	void CharacterJump(bool InIsJump)override;

	void Speaker()override;

	// Other
	void ActionDown() override;
	void ActionRise() override;
	void ReSetState()override;
	void SetDie() override;
	void AddDamage(AActor* WeaponActor, ECharacterDamagedType& damageType, F_Hp_Update_Value& resultDamage)override;
	void UpdateHpWidget()override;
	// AI
	void CheckTarget() override;

	// Player

	UFUNCTION(BlueprintCallable) void UpdateInterface(EPlayerInterfaceUpdate updateType) override;

	// Interaction
	void Interaction() override;
	void InteractionSelect(float Value)override;

	void SetSpawnerActor(AActor* InSpawnedActor)override;
	void SetDeleteSpawnedActor(AActor* InDeleteSpawnedActor)override;

	/*========================================================================================*/
	/*============================== 기본적 인 것 =====================================*/
protected:	
	// Interaction Overlap
	virtual void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)	PURE_VIRTUAL(ACBP_Character::OnComponentBeginOverlap, return;);
	virtual void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)														PURE_VIRTUAL(ACBP_Character::OnComponentEndOverlap, return;);

	// CharacterFunction에 정의해놓았음

protected:
	void Landed(FHitResult const& HitResults) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Hp") void AddHpUpdate(F_Hp_Update_Value const newAddHp);

	UFUNCTION(BlueprintCallable, Category = "Can Action") void CanArmming(bool& canArmming);
	UFUNCTION(BlueprintCallable, Category = "Can Action") void CanAttack(bool& canAttack);
	UFUNCTION(BlueprintCallable, Category = "Can Action") void CanDamaged(bool& canDamaged);
	UFUNCTION(BlueprintCallable, Category = "Can Action") void CanActionJump(bool& canJump);
	UFUNCTION(BlueprintCallable, Category = "Can Action") void CanMove(bool& canMove);
	UFUNCTION(BlueprintCallable, Category = "Can Action") void CanDodge(bool& canDodge);
	UFUNCTION(BlueprintCallable, Category = "Can Action") void CanDropping(bool& canDropping);
	UFUNCTION(BlueprintCallable, Category = "Can Action") void CanPickUpWeapon(EWeaponName const weaponName,bool& canPickUp);
	UFUNCTION(BlueprintCallable, Category = "Can Action") void CanAddItem(EItemName const itemName, bool& canAdd);
	UFUNCTION(BlueprintCallable, Category = "Can Action") void CanActionSkill(ESkillType const skillType, bool& canAction);

	UFUNCTION(BlueprintCallable, Category = "Attach") void AttachActorToCharacter(AActor* const Actor, bool const Equip);

	UFUNCTION(BlueprintCallable, Category = "Inventory") void AddInventory(bool const willAdd, AActor* const Actor, bool& Success);

	UFUNCTION(BlueprintCallable, Category = "State") void IsHostile(ECamp compare, bool& hostile);
	UFUNCTION(BlueprintCallable, Category = "State") void IsCharacterState(ECharacterState compare, bool& Same);


	UFUNCTION(BlueprintCallable, Category = "Skill") void SkillSpawn(TSubclassOf<class ACBP_Skill> skillClass, ACBP_Skill*& skill, ESkillType skillType = ESkillType::None);
	UFUNCTION(BlueprintCallable, Category = "Skill") void SkillStart();
	UFUNCTION(BlueprintCallable, Category = "Skill") void SkillEnd();

	UFUNCTION(BlueprintCallable, Category = "Jump") void JumpStart();
	UFUNCTION(BlueprintCallable, Category = "Jump") void JumpEnd();



	UFUNCTION() void SetSpawnLifeTime(float time);
	UFUNCTION() void EndSpawn();

	float lifeTime = -1;
	float curLifeTime = 0;


protected:
	UFUNCTION(BlueprintCallable, Category = "Hp") void UpdateHpValue();
	
	/*============================== 기본적 인 것 =====================================*/
protected :
	UPROPERTY(VisibleAnywhere) class USphereComponent* InteractionCollision;

public:
	UPROPERTY(VisibleAnywhere) class USceneComponent* center;

	UPROPERTY(VisibleAnywhere) class USceneComponent* targetTemp;

	UPROPERTY(BlueprintReadOnly, Category = "State") ECharacterState characterState = ECharacterState::Idle;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "State") ECamp camp = ECamp::Neutrality;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "State") ECharacterName characterName;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon") AActor* pair_Weapon;
	UPROPERTY(BlueprintReadOnly, Category = "Weapon") AActor* main_Weapon;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon") TArray<AActor*> weapon_Inventory;
	UPROPERTY(BlueprintReadOnly, Category = "Weapon") int cur_Using_Weapon_Num;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon") int max_Weapon_Inventory_Num;
	UPROPERTY(BlueprintReadOnly, Category = "Weapon") bool is_Switching_Weapon;

	UPROPERTY(BlueprintReadOnly, Category = "Attack") bool enable_Next_Attack;

	UPROPERTY(BlueprintReadOnly, Category = "Skill") TMap<ESkillType,bool> isPressedSkill ;
	UPROPERTY(BlueprintReadOnly, Category = "Skill") bool isGuard = false;

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item") UC_ItemInfoDataAsset* itemInfoDataAsset;

	UPROPERTY(BlueprintReadOnly, Category = "Item") TMap<EItemName,int> Item_Inventory;
	UPROPERTY(BlueprintReadOnly, Category = "Item") EItemName cur_Using_Item_Num;
	UPROPERTY(BlueprintReadOnly, Category = "Item") int max_Item_Inventory_Num;

	UPROPERTY(BlueprintReadOnly, Category = "Attack") int attack_Count;
	UPROPERTY(BlueprintReadOnly, Category = "Attack") bool cur_Attack_Is_End = true;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Hp") float curHp;
	UPROPERTY(BlueprintReadWrite, Category = "Hp") float maxHp;

	UPROPERTY(BlueprintReadOnly, Category = "Attack") AActor* target;
	UPROPERTY(BlueprintReadOnly, Category = "Attack") TArray<AActor*> targetCandidate;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Hp") TArray<F_Hp_Update_Value> hp_Value_Vector;
	UPROPERTY(BlueprintReadOnly, Category = "Hp") FTimerHandle hp_Update_Handle;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "DataAsset") UC_CharacterInfoDataAsset* character_InfoDataAsset;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "DataAsset") UC_CharacterMontageDataAsset* character_MontageDataAsset;


	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Jump") F_JumpData jump_Data;
	UPROPERTY(BlueprintReadOnly, Category = "Jump") float cur_Jump_Power;
	UPROPERTY(BlueprintReadOnly, Category = "Jump") bool is_Jump_Ready;

	UPROPERTY(BlueprintReadOnly, Category = "Mode") bool cur_CrouchMode;
	UPROPERTY(BlueprintReadOnly, Category = "Mode") bool cur_ZoomMode;


	UPROPERTY(BlueprintReadOnly, Category = "Temp") F_MontageData tempMontageData;

public:
	UFUNCTION(BlueprintCallable, Category = "Montage") void ClearMontageDelegate();

	UFUNCTION(BlueprintCallable, Category = "Montage") void AddMontageEndedDelegate();
	UFUNCTION(BlueprintCallable, Category = "Montage") void AddMontageStartedDelegate();
	UFUNCTION(BlueprintCallable, Category = "Montage") void AddMontageBlendOutDelegate();
	UFUNCTION(BlueprintCallable, Category = "Montage") void AddMontageNotifyBeginDelegate();
	UFUNCTION(BlueprintCallable, Category = "Montage") void AddMontageNotifyEndedDelegate();

	FString MontageDelegate;

protected:
	UFUNCTION() void ActionBlendOut();

	UFUNCTION() void CharacterOnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION() void CharacterOnMontageStarted(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION() void CharacterOnPlayMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);
	UFUNCTION() void CharacterOnPlayMontageNotifyEnd(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);
	UFUNCTION() void CharacterOnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted);

	virtual void BaseOnMontageBlendingOut() PURE_VIRTUAL(ACBP_Character::BaseOnMontageBlendingOut, return;);

	UFUNCTION(BlueprintCallable, Category = "Action") void ComboAction();

protected:
	bool ClearEndDelegate = true;
	bool ClearBeginDelegate = true;
	bool ClearNotifyBeginDelegate = true;
	bool ClearNotifyEndDelegate = true;
	bool ClearBlendOutDelegate = true;


protected:
	FTimerHandle hpTimerHandle;
	FTimerHandle CharacterSerchHandle;

public:
	bool bFallinged = false;


public:
	float GuardGauge = 500;
	bool canMoveBase = true;
	float MaxGuardGauge = 1000;

protected:
	float GuardGaugeSpeed = 100;

public:
	UFUNCTION(BlueprintCallable, Category = "Attack") void SerchCloseTarget();

private:
	TArray<AActor*> SpawnedActors;

};
