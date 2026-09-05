// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/CBP_NS_OutlineObject.h"
#include "Object/SimulationObject/Interaction_Object/Case/CBP_WeaponCase.h"

#include "../Pair_Weapon/CBP_PairWeapon.h"

#include "Interface/CBPI_Weapon.h"
#include "Interface/CBPI_CanGetAttackDataObject.h"

#include "Struct/SCharacter.h"
#include "Enums/EWeapon.h"

#include "DataAsset/C_MontageDataAsset.h"
#include "DataAsset/C_WeaponSocketDataAsset.h"
#include "DataAsset/C_WeaponCoolTimeDataAsset.h"

#include "CBP_MainWeapon.generated.h"

UCLASS()
class CPROJECT_API ACBP_MainWeapon : public ACBP_NS_OutlineObject ,public ICBPI_Weapon , public ICBPI_CanGetAttackDataObject
{
	GENERATED_BODY()

public:
	ACBP_MainWeapon();
	void OnConstruction(const FTransform& Transform) override;
protected:
	void Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType) override;
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
public:
	void Activate(bool InSuccess, bool& OutSuccess) override;
	void DeActivate(bool InSuccess, bool& OutSuccess) override;
	void UpdateInterface(bool Equip) override;

public:


	UFUNCTION(BlueprintCallable, Category = "Interaction") void DroppingMainWeapon(bool& Success);
	UFUNCTION(BlueprintCallable, Category = "Interaction") void PickUpWeapon(AActor* actor, bool& Success);

	UFUNCTION(BlueprintCallable, Category = "Set") void SetEquip(AActor* actor, bool const Equip);

	UFUNCTION(BlueprintCallable, Category = "Attack")	
		void GetMontageData(ECharacterName const characterName, ECharacterState const state, int const Combo, F_MontageData& result);
	UFUNCTION(BlueprintCallable, Category = "Attack")	
		void GetSkillMontageData(ECharacterName const characterName, ESkillType const skillType, F_WeaponSkillMontage& result , bool& canSkill);

	UFUNCTION(BlueprintCallable, Category = "Set") void SetSocket();

	UFUNCTION(BlueprintCallable, Category = "Attack")	void GetDamage(F_Hp_Update_Value& weaponDamage);
	UFUNCTION(BlueprintCallable, Category = "Attack")	void SetDamage(F_Hp_Update_Value const weaponDamage);
	UFUNCTION(BlueprintCallable, Category = "Skill") void UsingSkill(ESkillType skillType);
	// UI를 위한 함수(차피 이 값이 필요함)
	UFUNCTION(BlueprintCallable, Category = "Skill") void GetSkillCoolTime(ESkillType const skillType, F_WeaponSkillCoolTIme& result);
	UFUNCTION(BlueprintCallable, Category = "Skill") void SetSkillCoolTime();

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Setting") EWeaponName weaponName;

	UPROPERTY(BlueprintReadOnly, Category = "Socket") FName equip_Socket;
	UPROPERTY(BlueprintReadOnly, Category = "Socket") FName unEquip_Socket;

	UPROPERTY(BlueprintReadOnly, Category = "Damage") F_Hp_Update_Value damage;

	UPROPERTY(BlueprintReadOnly, Category = "PairWeapon")  ACBP_PairWeapon* pairWeapon;
	UPROPERTY(BlueprintReadOnly, Category = "Case") ACBP_WeaponCase* weaponCase;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Setting") EAttackType attackType;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Setting") EAttackHitType attackHitType;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Setting") FString widgetString = FString("NoName");

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Montage") TMap<ECharacterName, UC_MontageDataAsset* > montageDataAssets;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "DataAsset") UC_WeaponSocketDataAsset* socketDataAsset;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "DataAsset") UC_WeaponCoolTimeDataAsset* coolTimeDataAsset;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "BaseTrasnform") FVector main_Weapon_Scale = FVector(1, 1, 1);

//	UPROPERTY(BlueprintReadOnly, Category = "Case") TSubclassOf<ACBP_WeaponCase> weaponCaseClass;

	void SpawnTextActor(FString string, FVector Location, FVector fontColor = FVector(1, 1, 1), float fontSize = 24, float outlineFontSize = 1);

public:
	TMap<ESkillType, F_WeaponSkillCoolTIme> skillCoolTimes;

public:
	void GetInstigatorcharacter(ACBP_Character*& outCharacter)override;
	void GetFinalDamage(F_Hp_Update_Value& outDamage) override;

	void GetAttackType(EAttackType& outAttackType) override;
	void GetAttackHitType(EAttackHitType& outAttackHitType) override;

	void GetPushVector(FVector& outPushVector) override;
	void GetAttackPushType(EAttackPushType& outAttackPushType) override;

	void GetGuardSerchType(EGuardSerchType& outGuardSerchType) override;

	void GetCamp(ECamp& outCamp) override;
};
