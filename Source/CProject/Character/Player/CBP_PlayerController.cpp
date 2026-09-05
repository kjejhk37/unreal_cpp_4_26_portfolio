// Fill out your copyright notice in the Description page of Project Settings.


#include "CBP_PlayerController.h"
#include "character/Player/CBP_Player.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Quest/CBP_QuestActor.h"

#include "Macro/IncludeMacro.h"
#include "Macro/MyMacro.h"
#include "Logger/Logger.h"

#include MainWeaponPath
#include NS_InteractionPath
#include InteractionPath

void ACBP_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto* const WidgetClass = StaticLoadClass(UWCBP_PlayerInterfaceBase::StaticClass(), this, TEXT("WidgetBlueprint'/Game/CBP_Data/UI/WBP_PlayerInterface.WBP_PlayerInterface_C'"));

	playerInterface = CreateWidget<UWCBP_PlayerInterfaceBase>(this, WidgetClass, FName("PlayerWidget"));

	playerInterface->AddToViewport();

	textClass = StaticLoadClass(UWCBP_TextBase::StaticClass(), this, TEXT("WidgetBlueprint'/Game/CBP_Data/UI/WBP_Text.WBP_Text_C'"));
	textBoxClass = StaticLoadClass(UWCBP_TextBase::StaticClass(), this, TEXT("WidgetBlueprint'/Game/CBP_Data/UI/WBP_BoxText.WBP_BoxText_C'"));
	QuestTextClass = StaticLoadClass(UWCBP_QuestTextBase::StaticClass(), this, TEXT("WidgetBlueprint'/Game/CBP_Data/UI/WBP_QuestText.WBP_QuestText_C'"));
}

void ACBP_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ThisClass::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ThisClass::MoveRight);
	InputComponent->BindAxis("LookRight", this, &ThisClass::LookRight);
	InputComponent->BindAxis("LookUp", this, &ThisClass::LookUp);
	InputComponent->BindAxis("speaker", this, &ThisClass::speaker);

	InputComponent->BindAction("Dodge", EInputEvent::IE_Pressed, this, &ThisClass::Dodge);
	InputComponent->BindAction("Action", EInputEvent::IE_Pressed, this, &ThisClass::Action);
	InputComponent->BindAction("ActionDrop", EInputEvent::IE_Pressed, this, &ThisClass::ActionDrop);
	InputComponent->BindAction("GunReload", EInputEvent::IE_Pressed, this, &ThisClass::GunReload);

	InputComponent->BindAction("Skill_1", EInputEvent::IE_Pressed, this, &ThisClass::Skill_1);
	InputComponent->BindAction("Skill_2", EInputEvent::IE_Pressed, this, &ThisClass::Skill_2);
	InputComponent->BindAction("Skill_3", EInputEvent::IE_Pressed, this, &ThisClass::Skill_3);
	InputComponent->BindAction("Skill_4", EInputEvent::IE_Pressed, this, &ThisClass::Skill_4);

	InputComponent->BindAction("Skill_1", EInputEvent::IE_Released, this, &ThisClass::Skill_1_Released);
	InputComponent->BindAction("Skill_2", EInputEvent::IE_Released, this, &ThisClass::Skill_2_Released);
	InputComponent->BindAction("Skill_3", EInputEvent::IE_Released, this, &ThisClass::Skill_3_Released);
	InputComponent->BindAction("Skill_4", EInputEvent::IE_Released, this, &ThisClass::Skill_4_Released);

	InputComponent->BindAction("Weapon_1", EInputEvent::IE_Pressed, this, &ThisClass::Weapon_1);
	InputComponent->BindAction("Weapon_2", EInputEvent::IE_Pressed, this, &ThisClass::Weapon_2);
	InputComponent->BindAction("Weapon_3", EInputEvent::IE_Pressed, this, &ThisClass::Weapon_3);
	InputComponent->BindAction("Weapon_4", EInputEvent::IE_Pressed, this, &ThisClass::Weapon_4);

	InputComponent->BindAction("EquipOrUnEuip", EInputEvent::IE_Pressed, this, &ThisClass::EquipOrUnEuip);
		
	InputComponent->BindAction("Crouch", EInputEvent::IE_Pressed, this, &ThisClass::CrouchPressed);
	InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ThisClass::JumpPressed);
	InputComponent->BindAction("Zoom", EInputEvent::IE_Pressed, this, &ThisClass::ZoomPressed);

	InputComponent->BindAction("Crouch", EInputEvent::IE_Released, this, &ThisClass::CrouchReleased);
	InputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ThisClass::JumpReleased);
	InputComponent->BindAction("Zoom", EInputEvent::IE_Released, this, &ThisClass::ZoomReleased);

	InputComponent->BindAction("Interaction", EInputEvent::IE_Pressed, this, &ThisClass::Interaction);
	InputComponent->BindAxis("InteractionSelect", this, &ThisClass::InteractionSelect);


	// UsingItem
	InputComponent->BindAction("UsingItem", EInputEvent::IE_Pressed, this, &ThisClass::ItemUsing);
	InputComponent->BindAction("ChangeUsingItem", EInputEvent::IE_Pressed, this, &ThisClass::ChangeUsingItem);

}

void ACBP_PlayerController::SetIsUserControl(bool isUserControl)
{
	if (isUserControl)
		Cast<ACBP_Player>(GetPawn())->StopAIMoveToActor();

}

/* ==================================== PlayerInterface ======================================*/
void ACBP_PlayerController::Player_Hp_Interface()
{
	ACBP_Character* character = Cast<ACBP_Character>(GetPawn());
	if (character == nullptr) return;

	playerInterface->UpdateProgressBar(character->curHp, character->maxHp);
}

void ACBP_PlayerController::Player_Guard_Interface()
{
	ACBP_Character* character = Cast<ACBP_Character>(GetPawn());
	if (character == nullptr) return;

	playerInterface->UpdateGuardProgressBar(character->GuardGauge, character->MaxGuardGauge);
}

void ACBP_PlayerController::Player_Skill_Interface()
{
	ACBP_Character* character = Cast<ACBP_Character>(GetPawn());
	if (character == nullptr) return;

	TMap<ESkillType, F_WeaponSkillCoolTIme> skillCoolTimes;

	F_WeaponSkillCoolTIme temp;

	temp.skillType = ESkillType::Skill_1;
	MapAdd(skillCoolTimes, ESkillType::Skill_1, temp);

	temp.skillType = ESkillType::Skill_2;
	MapAdd(skillCoolTimes, ESkillType::Skill_2, temp);

	temp.skillType = ESkillType::Skill_3;
	MapAdd(skillCoolTimes, ESkillType::Skill_3, temp);

	temp.skillType = ESkillType::Skill_4;
	MapAdd(skillCoolTimes, ESkillType::Skill_4, temp);

	bool NoData = true;

	if (ACBP_MainWeapon* mainWeapon = Cast<ACBP_MainWeapon>(character->main_Weapon))
	{
		skillCoolTimes = mainWeapon->skillCoolTimes;
		NoData = false;
	}

	TArray<ESkillType> forData = { ESkillType::Skill_1,ESkillType::Skill_2 ,ESkillType::Skill_3 ,ESkillType::Skill_4 };

	for (ESkillType skillType : forData)
	{
		playerInterface->UpdateCoolTime(skillCoolTimes[skillType], NoData);
	}


}

void ACBP_PlayerController::Interface_TextDraw(FName WidgetName,FString string, FVector2D pos,bool isTextAnimation, float time, FVector2D speed)
{
	UWCBP_TextBase* textWidget = CreateWidget<UWCBP_TextBase>(this, textClass, WidgetName);
	textWidget->SetTextBox(string, FVector(1,1,1), pos,1, isTextAnimation, time, speed);

	textWidget->AddToViewport();

}

void ACBP_PlayerController::Interface_TextBoxDraw(FName WidgetName, FVector textBaseColor, FString string, FVector2D pos, float BaseAlpha, bool isTextAnimation, float time, FVector2D speed)
{
	UWCBP_TextBase* textWidget = CreateWidget<UWCBP_TextBase>(this, textBoxClass, WidgetName);
	textWidget->SetTextBox(string, textBaseColor, pos, BaseAlpha, isTextAnimation, time, speed);

	MapAdd(textBoxWidgets, WidgetName, textWidget);

	textWidget->AddToViewport();
}

void ACBP_PlayerController::Interface_InteractionTextUpdate()
{
	ACBP_Player* player = Cast<ACBP_Player>(GetPawn());
	if (player == nullptr) return;

	TArray<AActor*> interactionActors = player->interacitonActors;
	int const curInteractionSelectNum = player->curInteractionSelectNum;

	for (int i = 0; i < interactionActors.Num(); i++)
	{
		FName widgetName = FName(interactionActors[i]->GetName());
		FString widgetString = FString("");

		if (ACBP_NS_InteractionObject* interactionActor = Cast<ACBP_NS_InteractionObject>(interactionActors[i]))
			widgetString = interactionActor->widgetName;
		
		if (ACBP_Interaction_Object* interactionActor = Cast<ACBP_Interaction_Object>(interactionActors[i]))
			widgetString = interactionActor->widgetName;
		
		if (widgetString == FString("")) continue;
		if (textBoxWidgets.Contains(widgetName) == false) continue;

		if (i == curInteractionSelectNum)
			widgetString = FString(" F : ") + widgetString;

		FVector2D pos = FVector2D(300,0);
		float textBoxBaseAlpha = 1;

		pos.Y = (i - curInteractionSelectNum) * 60;
		textBoxBaseAlpha = 1 - (float(abs(i - curInteractionSelectNum)) / 3.0f);
		if (textBoxBaseAlpha < 0) textBoxBaseAlpha = 0;

		FVector textColor = (i == curInteractionSelectNum) ? FVector(1, 1, 0) : FVector(1, 1, 1);


		UWCBP_TextBase* textBoxWidget = textBoxWidgets[widgetName];
		
		textBoxWidget->SetTextBox(widgetString, textColor, pos, textBoxBaseAlpha);
	}

}
void ACBP_PlayerController::Interface_TextDelete(FName WidgetName)
{
	if (textBoxWidgets.Contains(WidgetName) == true)
	{
		textBoxWidgets[WidgetName]->RemoveFromViewport();
		textBoxWidgets[WidgetName]->MarkPendingKill();
		textBoxWidgets.Remove(WidgetName);
	}
}

void ACBP_PlayerController::Player_Inventory_Interface()
{
	ACBP_Character* character = Cast<ACBP_Character>(GetPawn());
	if (character == nullptr) return;

	TArray<AActor*> inventory = character->weapon_Inventory;
	int cur_Using_Weapon_Num = character->cur_Using_Weapon_Num;
	AActor* mainWeapon = character->main_Weapon;

	for (int i = 0; i < 4; i++)
	{
		FVector color = FVector(1, 1, 1);
		FString string = FString("None");

		if (i == cur_Using_Weapon_Num && mainWeapon != nullptr) color = FVector(1, 1, 0);

		if (inventory.IsValidIndex(i) == true)
		{
			if (ACBP_MainWeapon* object = Cast<ACBP_MainWeapon>(inventory[i]))
			{
				string = object->widgetString;
			}
		}

		playerInterface->UpdateInventory(string, color, i + 1);
	}
}

void ACBP_PlayerController::Player_Item_Inventory_Interface(FString itemNameString)
{
	FVector color = FVector(1, 1, 1);

	playerInterface->UpdateItemInventory(itemNameString, color);
}

void ACBP_PlayerController::Interface_QuestUpdate(TArray<AActor*> QuestActors)
{
	int UpdateNums = 0;
	float YLocation = -300;

	for (AActor* actor : QuestActors)
	{
		if (UpdateNums > 5) break;	// 0,1,2 번 퀘스트는 입력하고 3번쨰 부터는 안만들것
		
		FString widgetName = FString("QuestWidgetName_") + FString::FromInt(UpdateNums);

		ACBP_QuestActor* QuestActor = Cast<ACBP_QuestActor>(actor);
		if (QuestActor == nullptr) continue;

		if (QuestInterfaces.IsValidIndex(UpdateNums) == false)
		{
			UWCBP_QuestTextBase* QuestWidget = CreateWidget<UWCBP_QuestTextBase>(this, QuestTextClass, FName(widgetName));
			QuestWidget->AddToViewport();
			QuestInterfaces.Add(QuestWidget);
		}

		UWCBP_QuestTextBase* curQuestWidget = QuestInterfaces[UpdateNums];

		// 여기서 값을 저장 + 메인 하나 와 1차서브퀘스트만 입력 할 것

		FText mainQuestText = QuestActor->QuestName;
		curQuestWidget->MainQuestInterfaceUpdate(mainQuestText);

		TArray<FText> subQuestTexts;
		for (ACBP_QuestActor* subQuest : QuestActor->SpawnedSubQuests)
		{
			FText subQuestName = subQuest->QuestName;
			subQuestTexts.Add(subQuestName);
		}
		
		curQuestWidget->SubQuestInterfaceUpdate(subQuestTexts);
		curQuestWidget->SetRenderTranslation(FVector2D(0, YLocation));


		YLocation = YLocation + 20 + 30 * subQuestTexts.Num() + 30;


		// 여기서 값을 저장
		
		UpdateNums++;
	}

	for (int i = QuestInterfaces.Num(); i >= UpdateNums; i--)
	{
		if (QuestInterfaces.IsValidIndex(i) == true)
		{
			QuestInterfaces[i]->RemoveFromViewport();
			QuestInterfaces[i]->MarkPendingKill();

			QuestInterfaces.RemoveAt(i);
		}
	}


}

void ACBP_PlayerController::Player_RemainBullet_Interface(int maxBullet, int curBullet)
{
	playerInterface->UpdateRemainBullet(maxBullet, curBullet);
}

void ACBP_PlayerController::Player_RemainBullet_Interface_newVisible(bool newVisible)
{
	playerInterface->UpdateRemainBullet_newVisible(newVisible);
}

void ACBP_PlayerController::Player_Jump_Interface(float curJumpPower, float minJumpPower, float maxJumpPower)
{
	playerInterface->UpdateJumpGaugeProgressBar(curJumpPower, minJumpPower, maxJumpPower);
}

void ACBP_PlayerController::Player_Jump_Interface_newVisible(bool newVisible)
{
	playerInterface->UpdateJumpGaugeProgressBar_newVisible(newVisible);
}





/* ==================================== Binding Function ======================================*/
void ACBP_PlayerController::MoveRight(float const Value)
{
	if(auto* player = Cast<ACBP_Player>(GetPawn()))
	{

		bool canMove = false;
		player->CanMove(canMove);

		player->dodgeRight = Value;

		if (!canMove) return;

		FVector Direction = FQuat(FRotator(0, GetControlRotation().Yaw, 0)).GetRightVector();
		player->AddMovementInput(Direction, Value, false);

		ThisClass::SetIsUserControl((Value == 1 || Value == -1));
	}
}

void ACBP_PlayerController::MoveForward(float const Value)
{
	if(auto* player = Cast<ACBP_Player>(GetPawn()))
	{
		bool canMove = false;
		player->CanMove(canMove);

		player->dodgeForward = Value;

		if (!canMove) return;

		FVector Direction = FQuat(FRotator(0, GetControlRotation().Yaw, 0)).GetForwardVector();
		player->AddMovementInput(Direction, Value, false);

		ThisClass::SetIsUserControl((Value == 1 || Value == -1));
	}
}

void ACBP_PlayerController::LookRight(float const Value)
{
	AddYawInput(Value);

	ThisClass::SetIsUserControl((Value == 1));
}

void ACBP_PlayerController::LookUp(float const Value)
{
	AddPitchInput(Value);

	ThisClass::SetIsUserControl((Value == -1));
}

void ACBP_PlayerController::speaker(float const Value)
{
	if (auto* character = Cast<ACBP_Character>(GetPawn()))
	{
		if (Value != 1) return;

		character->Speaker();
		ThisClass::SetIsUserControl(true);
	}
}

 /*========================================= Action Mapping ====================================*/


void ACBP_PlayerController::Dodge()
{
	if (auto* character = Cast<ACBP_Character>(GetPawn()))
	{
//		if (character->GetCharacterMovement()->IsFalling() == true)
//			return;

		character->ActionDodge();
		ThisClass::SetIsUserControl(true);

//		Logger::Print(FString("Dodge"), 0,10);
	}
}

void ACBP_PlayerController::Action()
{
	if (auto* character = Cast<ACBP_Character>(GetPawn()))
	{
		character->Action();
		ThisClass::SetIsUserControl(true);

//		Logger::Print(FString("Action"), 0, 10);
	}
}
void ACBP_PlayerController::ActionDrop()
{
	if (auto* character = Cast<ACBP_Character>(GetPawn()))
	{
		bool Success;
		character->ActionDropping(Success);
		ThisClass::SetIsUserControl(true);

//		Logger::Print(FString("ActionDrop"), 0, 10);
	}
}

void ACBP_PlayerController::GunReload()
{
	if (auto* character = Cast<ACBP_Character>(GetPawn()))
	{
		character->GunReLoad();
		ThisClass::SetIsUserControl(true);

//		Logger::Print(FString("GunReLoad"), 0, 10);
	}
}

/* ================================== Skill =================================*/

void ACBP_PlayerController::Skill_1()
{
	if (auto* character = Cast<ACBP_Character>(GetPawn()))
	{
		character->Skill(ESkillType::Skill_1, true);
		ThisClass::SetIsUserControl(true);

//		Logger::Print(FString("Skill_1"), 0, 10);
	}
}
void ACBP_PlayerController::Skill_2()
{
	if (auto* character = Cast<ACBP_Character>(GetPawn()))
	{
		character->Skill(ESkillType::Skill_2, true);
		ThisClass::SetIsUserControl(true);

//		Logger::Print(FString("Skill_2"), 0, 10);
	}
}
void ACBP_PlayerController::Skill_3()
{
	if (auto* character = Cast<ACBP_Character>(GetPawn()))
	{
		character->Skill(ESkillType::Skill_3,true);
		ThisClass::SetIsUserControl(true);

//		Logger::Print(FString("Skill_3"), 0, 10);
	}
}
void ACBP_PlayerController::Skill_4()
{
	if (auto* character = Cast<ACBP_Character>(GetPawn()))
	{
		character->Skill(ESkillType::Skill_4, true);
		ThisClass::SetIsUserControl(true);

//		Logger::Print(FString("Skill_4"), 0, 10);
	}
}

void ACBP_PlayerController::Skill_1_Released()
{
	if (auto* character = Cast<ACBP_Character>(GetPawn()))
	{
		character->Skill(ESkillType::Skill_1, false);
		ThisClass::SetIsUserControl(true);
	}
}
void ACBP_PlayerController::Skill_2_Released()
{
	if (auto* character = Cast<ACBP_Character>(GetPawn()))
	{
		character->Skill(ESkillType::Skill_2, false);
		ThisClass::SetIsUserControl(true);

//		Logger::Print(FString("Skill_1"), 0, 10);
	}
}

void ACBP_PlayerController::Skill_3_Released()
{
	if (auto* character = Cast<ACBP_Character>(GetPawn()))
	{
		character->Skill(ESkillType::Skill_3, false);
		ThisClass::SetIsUserControl(true);

//		Logger::Print(FString("Skill_1"), 0, 10);
	}
}

void ACBP_PlayerController::Skill_4_Released()
{
	if (auto* character = Cast<ACBP_Character>(GetPawn()))
	{
		character->Skill(ESkillType::Skill_4, false);
		ThisClass::SetIsUserControl(true);

//		Logger::Print(FString("Skill_1"), 0, 10);
	}
}

/* ====================================== Weapon ==========================================*/
void ACBP_PlayerController::Weapon_1()
{
	if (auto* character = Cast<ACBP_Character>(GetPawn()))
	{
		character->WeaponSelect(0);
		ThisClass::SetIsUserControl(true);

//		Logger::Print(FString("Weapon_1"), 0, 10);
	}
}
void ACBP_PlayerController::Weapon_2()
{
	if (auto* character = Cast<ACBP_Character>(GetPawn()))
	{
		character->WeaponSelect(1);
		ThisClass::SetIsUserControl(true);

//		Logger::Print(FString("Weapon_2"), 0, 10);
	}
}
void ACBP_PlayerController::Weapon_3()
{
	if (auto* character = Cast<ACBP_Character>(GetPawn()))
	{
		character->WeaponSelect(2);
		ThisClass::SetIsUserControl(true);

//		Logger::Print(FString("Weapon_3"), 0, 10);
	}
}
void ACBP_PlayerController::Weapon_4()
{
	if (auto* character = Cast<ACBP_Character>(GetPawn()))
	{
		character->WeaponSelect(3);
		ThisClass::SetIsUserControl(true);

//		Logger::Print(FString("Weapon_4"), 0, 10);
	}
}

void ACBP_PlayerController::EquipOrUnEuip()
{
	if (auto* character = Cast<ACBP_Character>(GetPawn()))
	{
		character->EquipOrUnEquip();
		ThisClass::SetIsUserControl(true);

//		Logger::Print(FString("EquipOrUnEquip"), 0, 10);
	}
}

void ACBP_PlayerController::CrouchPressed()
{
	if (auto* character = Cast<ACBP_Character>(GetPawn()))
	{
		character->CharacterCrouch(true);
		ThisClass::SetIsUserControl(true);
	}
}

void ACBP_PlayerController::CrouchReleased()
{
	if (auto* character = Cast<ACBP_Character>(GetPawn()))
	{
		character->CharacterCrouch(false);
		ThisClass::SetIsUserControl(true);
	}
}

void ACBP_PlayerController::JumpPressed()
{
	if (auto* character = Cast<ACBP_Character>(GetPawn()))
	{
		character->CharacterJump(true);
		ThisClass::SetIsUserControl(true);
	}
}

void ACBP_PlayerController::JumpReleased()
{
	if (auto* character = Cast<ACBP_Character>(GetPawn()))
	{
		character->CharacterJump(false);
		ThisClass::SetIsUserControl(true);
	}
}

void ACBP_PlayerController::ZoomPressed()
{
	if (auto* character = Cast<ACBP_Character>(GetPawn()))
	{
		character->ZoomCameraIn();
		ThisClass::SetIsUserControl(true);
	}
}

void ACBP_PlayerController::ZoomReleased()
{
	if (auto* character = Cast<ACBP_Character>(GetPawn()))
	{
		character->ZoomCameraOut();
		ThisClass::SetIsUserControl(true);
	}
}

/* =========================== Interaction =================================*/

void ACBP_PlayerController::Interaction()
{
	if (auto* character = Cast<ACBP_Character>(GetPawn()))
	{
		character->Interaction();
		ThisClass::SetIsUserControl(true);
	}
}

void ACBP_PlayerController::InteractionSelect(float const Value)
{
	if (auto* character = Cast<ACBP_Character>(GetPawn()))
	{
		character->InteractionSelect(Value);
		ThisClass::SetIsUserControl(true);
	}
}

void ACBP_PlayerController::ItemUsing()
{
	if (auto* character = Cast<ACBP_Character>(GetPawn()))
	{
		bool outSuccess;
		character->UsingItem(EItemName::None,1, outSuccess);
		ThisClass::SetIsUserControl(true);
	}
}

void ACBP_PlayerController::ChangeUsingItem()
{
	if (auto* character = Cast<ACBP_Character>(GetPawn()))
	{
		character->UsingItemNumIncreasing();
		ThisClass::SetIsUserControl(true);
	}
}