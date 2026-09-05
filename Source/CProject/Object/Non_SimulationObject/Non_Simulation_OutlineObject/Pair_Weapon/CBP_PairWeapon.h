// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/CBP_NS_OutlineObject.h"

#include "Interface/CBPI_Weapon.h"
#include "Interface/CBPI_CanGetAttackDataObject.h"

#include "Struct/SCharacter.h"
#include "Enums/EWeapon.h"
#include "CBP_PairWeapon.generated.h"

UCLASS()
class CPROJECT_API ACBP_PairWeapon : 
	public ACBP_NS_OutlineObject,
	public ICBPI_Weapon,
	public ICBPI_CanGetAttackDataObject
{
	GENERATED_BODY()

public:
	ACBP_PairWeapon();
	void OnConstruction(const FTransform& Transform) override;
protected:
	void Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType) override;
	virtual void BeginPlay() override;

public:
	void Activate(bool InSuccess, bool& OutSuccess) override;
	void DeActivate(bool InSuccess, bool& OutSuccess) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Interaction") void DroppingPairWeapon(AActor* mainWeapon, bool& Success);
	UFUNCTION(BlueprintCallable, Category = "Interaction") void PickUpWeapon(AActor* actor, bool& Success);

	UFUNCTION(BlueprintCallable, Category = "Set") void SetEquip(bool const Equip);



	UFUNCTION(BlueprintCallable, Category = "Attack") void GetDamage(F_Hp_Update_Value& outDamage);
	UFUNCTION(BlueprintCallable, Category = "Attack") void SetDamage(F_Hp_Update_Value const inDamage);


public:
	UPROPERTY(BlueprintReadOnly, Category = "Socket") FName equip_Socket;
	UPROPERTY(BlueprintReadOnly, Category = "Socket") FName unEquip_Socket;

	UPROPERTY(BlueprintReadOnly, Category = "Damage") F_Hp_Update_Value damage;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "BaseTrasnform") FVector pair_Weapon_Scale = FVector(1,1,1);

	void SpawnTextActor(FString string, FVector Location, FVector fontColor = FVector(1, 1, 1), float fontSize = 24, float outlineFontSize = 1);

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Setting") EAttackType attackType;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Setting") EAttackHitType attackHitType;

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
