// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UI/WCBP_PlayerInterfaceBase.h"
#include "UI/WCBP_TextBase.h"
#include "UI/WCBP_QuestTextBase.h"

#include "CBP_PlayerController.generated.h"

UCLASS()
class CPROJECT_API ACBP_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable) void SetIsUserControl(bool isUserControl);

	void Player_Hp_Interface();
	void Player_Guard_Interface();
	void Player_Jump_Interface(float curJumpPower,float minJumpPower, float maxJumpPower);
	void Player_Jump_Interface_newVisible(bool newVisible);



	void Player_Skill_Interface();
	void Player_Inventory_Interface();
	void Player_Item_Inventory_Interface(FString itemNameString);

	void Player_RemainBullet_Interface(int maxBullet,int curBullet);
	void Player_RemainBullet_Interface_newVisible(bool newVisible);


	void Interface_TextDraw(FName WidgetName, FString string, FVector2D pos, bool isTextAnimation, float time, FVector2D speed);
	void Interface_TextBoxDraw(FName WidgetName, FVector textBaseColor, FString string, FVector2D pos,float BaseAlpha, bool isTextAnimation, float time, FVector2D speed);

	void Interface_InteractionTextUpdate();
	void Interface_TextDelete(FName WidgetName);

private:
	void SetupInputComponent() override;

public:
	void Interface_QuestUpdate(TArray<AActor*> QuestActors);

protected:
	UPROPERTY(BlueprintReadOnly) TArray<UWCBP_QuestTextBase*> QuestInterfaces;
	UPROPERTY(BlueprintReadOnly) TSubclassOf<UWCBP_QuestTextBase> QuestTextClass;

protected:
	UPROPERTY(BlueprintReadOnly) class UWCBP_PlayerInterfaceBase* playerInterface;
	UPROPERTY(BlueprintReadOnly) TSubclassOf<UWCBP_TextBase> textClass;
	UPROPERTY(BlueprintReadOnly) TSubclassOf<UWCBP_TextBase> textBoxClass;

	TMap<FName,UWCBP_TextBase*> textBoxWidgets;

private:
	void MoveRight(float const Value);
	void MoveForward(float const Value);

	void LookRight(float const Value);
	void LookUp(float const Value);

	void speaker(float const Value);

	void Dodge();
	void Action();
	void ActionDrop();
	void GunReload();

	void Skill_1();
	void Skill_2();
	void Skill_3();
	void Skill_4();

	void Skill_1_Released();
	void Skill_2_Released();
	void Skill_3_Released();
	void Skill_4_Released();

	void Weapon_1();
	void Weapon_2();
	void Weapon_3();
	void Weapon_4();

	void EquipOrUnEuip();

	void CrouchPressed();
	void CrouchReleased();

	void JumpPressed();
	void JumpReleased();

	void ZoomPressed();
	void ZoomReleased();
	
	void Interaction();
	void InteractionSelect(float const Value);

	void ItemUsing();
	void ChangeUsingItem();
};
