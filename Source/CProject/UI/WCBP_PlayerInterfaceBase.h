// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Struct/SWeapon.h"
#include "WCBP_PlayerInterfaceBase.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API UWCBP_PlayerInterfaceBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct();


public:
	UFUNCTION(BlueprintCallable) void UpdateProgressBar(float curHp, float maxHp);
	UFUNCTION(BlueprintCallable) void UpdateGuardProgressBar(float curValue, float maxValue);


	UFUNCTION(BlueprintCallable) void UpdateCoolTime(F_WeaponSkillCoolTIme coolTimeData,bool NoData);

	UFUNCTION(BlueprintCallable) void UpdateInventory(FString string, FVector color, int inventoryNum);

	UFUNCTION(BlueprintCallable) void UpdateItemInventory(FString string, FVector color);

	UFUNCTION(BlueprintCallable) void UpdateJumpGaugeProgressBar(float curJumpPower, float minJumpPower, float maxJumpPower);
	UFUNCTION(BlueprintCallable) void UpdateJumpGaugeProgressBar_newVisible(bool newVisible);

	UFUNCTION(BlueprintCallable) void UpdateRemainBullet(int maxBullet,int curBullet);
	UFUNCTION(BlueprintCallable) void UpdateRemainBullet_newVisible(bool newVisible);

protected:
//	UFUNCTION() void OnButtonClicked();

};
