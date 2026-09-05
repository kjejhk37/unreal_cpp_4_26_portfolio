// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WCBP_QuestTextBase.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Blueprint/UserWidget.h"


void UWCBP_QuestTextBase::MainQuestInterfaceUpdate(FText text)
{
	UTextBlock* textBox = Cast<UTextBlock>(GetWidgetFromName(FName("MainQuestText")));
	if (textBox == nullptr) return;

	FString mainQuestText = FString("* ") + text.ToString();

	textBox->SetText(FText::FromString(mainQuestText));
}

void UWCBP_QuestTextBase::SubQuestInterfaceUpdate(TArray<FText> texts)
{
	int i = 1;

	for (FText text : texts)
	{
		FString textName = FString("SubQuestText_0") + FString::FromInt(i);

		UTextBlock* textBox = Cast<UTextBlock>(GetWidgetFromName(FName(textName)));
		if (textBox == nullptr) return;

		FString subQuestText = FString("    * ") + text.ToString();

		textBox->SetText(FText::FromString(subQuestText));
		i++;
	}

	for (int k = 6; k >= i; k--)
	{
		FString textName = FString("SubQuestText_0") + FString::FromInt(k);

		UTextBlock* textBox = Cast<UTextBlock>(GetWidgetFromName(FName(textName)));
		if (textBox == nullptr) return;

		textBox->SetText(FText());
	}

	UImage* image = Cast<UImage>(GetWidgetFromName(FName("SubQuestImage")));
	if (image == nullptr) return;
	image->SetRenderScale(FVector2D(1, i - 1));
}