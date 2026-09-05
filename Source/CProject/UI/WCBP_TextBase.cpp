// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WCBP_TextBase.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Blueprint/UserWidget.h"

#include "Macro/MyMacro.h"

void UWCBP_TextBase::SetTextBox(FString string, FVector textBaseColor, FVector2D pos, float textBaseAlpha, bool isTextAnimation, float time, FVector2D speed)
{
	UTextBlock* textBox = Cast<UTextBlock>(GetWidgetFromName(FName("TextBox")));
	if (textBox == nullptr) return;

	textBox->SetText(FText::FromString(string));

	FWidgetTransform trasnform;
	trasnform.Translation = pos;
	trasnform.Scale = FVector2D(1, 1);

	textBox->SetRenderTransform(trasnform);

	BaseAlpha = textBaseAlpha;

	textBox->SetColorAndOpacity(FLinearColor(textBaseColor.X, textBaseColor.Y, textBaseColor.Z, BaseAlpha));

	deleteTime = time;
	moveSpeed = speed;

	curTime = 0;
	isAnimation = isTextAnimation;
	BaseColor = textBaseColor;
	UImage* textBoxImage = Cast<UImage>(GetWidgetFromName(FName("TextBoxImage")));
	if (textBoxImage == nullptr) return;

	textBoxImage->SetRenderTransform(trasnform);
	textBoxImage->SetColorAndOpacity(FLinearColor(0, 0, 0, BaseAlpha * 0.5f));
}

void UWCBP_TextBase::SetTextString(FString string)					 
{
	UTextBlock* textBox = Cast<UTextBlock>(GetWidgetFromName(FName("TextBox")));
	if (textBox == nullptr) return;

	textBox->SetText(FText::FromString(string));
}


void UWCBP_TextBase::SetTextPos(FVector2D pos)						 
{
	UTextBlock* textBox = Cast<UTextBlock>(GetWidgetFromName(FName("TextBox")));
	if (textBox == nullptr) return;

	FWidgetTransform trasnform;
	trasnform.Translation = pos;
	trasnform.Scale = FVector2D(1, 1);

	textBox->SetRenderTransform(trasnform);


}
void UWCBP_TextBase::SetTextBaseColor(FLinearColor textBaseColor)
{
	UTextBlock* textBox = Cast<UTextBlock>(GetWidgetFromName(FName("TextBox")));
	if (textBox == nullptr) return;

	BaseAlpha = textBaseColor.A;
	FSlateColor color = textBox->ColorAndOpacity;

	BaseColor = FVector(textBaseColor.R, textBaseColor.G, textBaseColor.B);
	
	textBox->SetColorAndOpacity(textBaseColor);


}
void UWCBP_TextBase::SetTextSetAnimaiton(bool isTextAnimation)		 
{
	isAnimation = isTextAnimation;
}
void UWCBP_TextBase::SetTextAnimationTime(float time)				 
{
	curTime = time;
}

void UWCBP_TextBase::SetTextAnimationVelocity(FVector2D speed)		 
{
	moveSpeed = speed;
}

void UWCBP_TextBase::SetTextFont(float fontSize)
{
	UTextBlock* textBox = Cast<UTextBlock>(GetWidgetFromName(FName("TextBox")));
	if (textBox == nullptr) return;

	textBox->Font.Size = fontSize;
}

void UWCBP_TextBase::SetTextOutlineFont(float fontSize)
{
	UTextBlock* textBox = Cast<UTextBlock>(GetWidgetFromName(FName("TextBox")));
	if (textBox == nullptr) return;

	textBox->Font.OutlineSettings.OutlineSize = fontSize;
}

void UWCBP_TextBase::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// 로직 구현
	if (isAnimation == false) return;
	UTextBlock* textBox = Cast<UTextBlock>(GetWidgetFromName(FName("TextBox")));
	if (textBox == nullptr) return;

	curTime += InDeltaTime;

	FWidgetTransform trasnform = textBox->RenderTransform;
	trasnform.Translation += moveSpeed * InDeltaTime;
	textBox->SetRenderTransform(trasnform);

	float alpha = BaseAlpha * (1 - (curTime / deleteTime) * (curTime / deleteTime));
//	float alpha = BaseAlpha;
	textBox->SetColorAndOpacity(FLinearColor(BaseColor.X, BaseColor.Y, BaseColor.Z, alpha));

//	textBox->Font.OutlineSettings.OutlineColor = FLinearColor(0, 0, 0, alpha);

	if (UImage* textBoxImage = Cast<UImage>(GetWidgetFromName(FName("TextBoxImage"))))
	{
		textBoxImage->SetRenderTransform(trasnform);
		textBoxImage->SetColorAndOpacity(FLinearColor(0, 0, 0, alpha * 0.5f));
	}

	if (curTime > deleteTime)
	{
		if (IsValid(this) == true)
		{
			this->RemoveFromViewport();		// 안보이게 하기
			this->MarkPendingKill();		// 메모리 지우기
		}
	}

}