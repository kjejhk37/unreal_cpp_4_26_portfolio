// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WCBP_PlayerInterfaceBase.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Button.h"

#include "Character/Player/CBP_PlayerController.h"
#include "Character/Player/CBP_Player.h"

#include "Logger/Logger.h"

void UWCBP_PlayerInterfaceBase::NativeConstruct()
{
	Super::NativeConstruct();

//	// 위젯이 생성되면 버튼의 OnClicked 이벤트에 핸들러 함수를 연결합니다.
//	UButton* itemChangeButton = Cast<UButton>(GetWidgetFromName(FName("ItemChange")));
//
//	if (itemChangeButton)
//	{
//		itemChangeButton->OnClicked.AddDynamic(this, &UWCBP_PlayerInterfaceBase::OnButtonClicked);
//	}
}

void UWCBP_PlayerInterfaceBase::UpdateProgressBar(float curHp, float maxHp)
{
	UProgressBar* progressBar = Cast<UProgressBar>(GetWidgetFromName(FName("HP_Bar")));
	if (progressBar == nullptr) return;

	UTextBlock* hp_Value_Box = Cast<UTextBlock>(GetWidgetFromName(FName("HP_Value")));
	if (hp_Value_Box != nullptr)
	{
		FString string = FString::FromInt(curHp) + FString(" / ") + FString::FromInt(maxHp);

		FText text = FText::FromString(string);

		hp_Value_Box->SetText(text);
	}


	progressBar->SetPercent(curHp / maxHp);
}

void UWCBP_PlayerInterfaceBase::UpdateGuardProgressBar(float curValue, float maxValue)
{
	UProgressBar* progressBar = Cast<UProgressBar>(GetWidgetFromName(FName("GuardGauge_Bar")));
	if (progressBar == nullptr) return;

	progressBar->SetPercent(curValue / maxValue);
}

void UWCBP_PlayerInterfaceBase::UpdateCoolTime(F_WeaponSkillCoolTIme coolTimeData, bool NoData)
{
	FName stackBoxName;
	FName coolTimeBoxName;
	FName progressBoxName;

	switch (coolTimeData.skillType)
	{
	case ESkillType::Skill_1:
		stackBoxName = FName("Skill_01_Stack");
		coolTimeBoxName = FName("Skill_01_CoolTime");
		progressBoxName = FName("Skill_01");
		break;
	case ESkillType::Skill_2:
		stackBoxName = FName("Skill_02_Stack");
		coolTimeBoxName = FName("Skill_02_CoolTime");
		progressBoxName = FName("Skill_02");
		break;
	case ESkillType::Skill_3:
		stackBoxName = FName("Skill_03_Stack");
		coolTimeBoxName = FName("Skill_03_CoolTime");
		progressBoxName = FName("Skill_03");
		break;
	case ESkillType::Skill_4:
		stackBoxName = FName("Skill_04_Stack");
		coolTimeBoxName = FName("Skill_04_CoolTime");
		progressBoxName = FName("Skill_04");
		break;
	}

	UTextBlock* stackBox = Cast<UTextBlock>(GetWidgetFromName(stackBoxName));
	UTextBlock* coolTimeBox = Cast<UTextBlock>(GetWidgetFromName(coolTimeBoxName));
	UProgressBar* progressBox = Cast<UProgressBar>(GetWidgetFromName(progressBoxName));

	if (NoData == false)
	{
		if (stackBox != nullptr)
		{
			FText text = FText::FromString(FString::FromInt(coolTimeData.curSkillStack));
			stackBox->SetText(text);
		}

		if (coolTimeBox != nullptr)
		{
			float remainCoolTime = (coolTimeData.CoolTime - coolTimeData.curCoolTime);

			int pointerUpper = int(remainCoolTime);
			int pointerUnder = int(remainCoolTime * 10 - pointerUpper*10);

			FString string = FString::FromInt(pointerUpper) + FString(".") + FString::FromInt(pointerUnder);
			FText text = FText::FromString(string);
			coolTimeBox->SetText(text);
		}

		if (progressBox != nullptr)
		{
			progressBox->SetPercent(coolTimeData.curCoolTime / coolTimeData.CoolTime);
		}
	}

	if (NoData == true)
	{
		if (stackBox != nullptr)
		{
			FText text = FText::FromString(FString(" "));
			stackBox->SetText(text);
		}

		if (coolTimeBox != nullptr)
		{
			FText text = FText::FromString(FString(" "));
			coolTimeBox->SetText(text);
		}

		if (progressBox != nullptr)
		{
			progressBox->SetPercent(0);
		}
	}
}

void UWCBP_PlayerInterfaceBase::UpdateInventory(FString string, FVector color, int inventoryNum)
{
	// Inventory_01_Text
	FName textName = FName(FString("Inventory_0") + FString::FromInt(inventoryNum) + FString("_Text"));
	UTextBlock* textBox = Cast<UTextBlock>(GetWidgetFromName(textName));
	if (textBox == nullptr) return;

	textBox->SetText(FText::FromString(string));
	textBox->SetColorAndOpacity(FLinearColor(color.X, color.Y, color.Z, 1));
}

void UWCBP_PlayerInterfaceBase::UpdateItemInventory(FString string, FVector color)
{
	UTextBlock* textBox = Cast<UTextBlock>(GetWidgetFromName(FName("Inventory_Item")));
	if (textBox == nullptr) return;

	textBox->SetText(FText::FromString(string));
	textBox->SetColorAndOpacity(FLinearColor(color.X, color.Y, color.Z, 1));
}

void UWCBP_PlayerInterfaceBase::UpdateJumpGaugeProgressBar(float curJumpPower, float minJumpPower, float maxJumpPower)
{
	UProgressBar* progressBar = Cast<UProgressBar>(GetWidgetFromName(FName("JumpGauge")));
	if (progressBar == nullptr) return;

	float curValue = curJumpPower - minJumpPower;
	float maxValue = maxJumpPower - minJumpPower;

	progressBar->SetPercent(curValue / maxValue);

	UTextBlock* textBox = Cast<UTextBlock>(GetWidgetFromName(FName("JumpGaugeText")));
	if (textBox == nullptr) return;

	FString str = FString::FromInt(curJumpPower) + FString(" / ") + FString::FromInt(maxJumpPower);

	textBox->SetText(FText::FromString(str));

}

void UWCBP_PlayerInterfaceBase::UpdateJumpGaugeProgressBar_newVisible(bool newVisible)
{
	UProgressBar* progressBar = Cast<UProgressBar>(GetWidgetFromName(FName("JumpGauge")));
	if (progressBar == nullptr) return;

	if (newVisible == true)
	{
		progressBar->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		progressBar->SetVisibility(ESlateVisibility::Hidden);
	}

	UTextBlock* textBox = Cast<UTextBlock>(GetWidgetFromName(FName("JumpGaugeText")));
	if (textBox == nullptr) return;

	if (newVisible == true)
	{
		textBox->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		textBox->SetVisibility(ESlateVisibility::Hidden);
	}

}

void UWCBP_PlayerInterfaceBase::UpdateRemainBullet(int maxBullet, int curBullet)
{
	UTextBlock* RemainBulletTextBox = Cast<UTextBlock>(GetWidgetFromName("RemainBulletText"));
	UTextBlock* curRemainBulletTextBox = Cast<UTextBlock>(GetWidgetFromName("curRemainBulletText"));
	if (RemainBulletTextBox == nullptr) return;
	if (curRemainBulletTextBox == nullptr) return;

	FString string = FString::FromInt(curBullet) + FString(" / ") + FString::FromInt(maxBullet);
	curRemainBulletTextBox->SetText(FText::FromString(string));
}

void UWCBP_PlayerInterfaceBase::UpdateRemainBullet_newVisible(bool newVisible)
{
	UTextBlock* RemainBulletTextBox = Cast<UTextBlock>(GetWidgetFromName("RemainBulletText"));
	UTextBlock* curRemainBulletTextBox = Cast<UTextBlock>(GetWidgetFromName("curRemainBulletText"));
	if (RemainBulletTextBox == nullptr) return;
	if (curRemainBulletTextBox == nullptr) return;

	if (newVisible == true)
	{
		RemainBulletTextBox->SetVisibility(ESlateVisibility::Visible);
		curRemainBulletTextBox->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		RemainBulletTextBox->SetVisibility(ESlateVisibility::Hidden);
		curRemainBulletTextBox->SetVisibility(ESlateVisibility::Hidden);
	}

}

/*
void UWCBP_PlayerInterfaceBase::OnButtonClicked()
{
	ACBP_PlayerController* playerController = Cast<ACBP_PlayerController>(GetOwningPlayer());
	if (playerController == nullptr) return;

	ACBP_Character* character = Cast<ACBP_Character>(playerController->GetPawn());
	if (character == nullptr) return;

	character->UsingItemNumIncreasing();
}

*/