// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WCBP_TextBase.generated.h"


UCLASS()
class CPROJECT_API UWCBP_TextBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable) void SetTextBox(FString string = FString(""),FVector textBaseColor = FVector(1,1,1),FVector2D pos = FVector2D(0,0),float textBaseAlpha = 1,bool isTextAnimation = false, float time = 1.0f, FVector2D speed = FVector2D(1,1));
	UFUNCTION(BlueprintCallable) void SetTextFont(float fontSize);
	UFUNCTION(BlueprintCallable) void SetTextOutlineFont(float fontSize);

	UFUNCTION(BlueprintCallable) void SetTextString(FString string);
	UFUNCTION(BlueprintCallable) void SetTextPos(FVector2D pos);
	UFUNCTION(BlueprintCallable) void SetTextBaseColor(FLinearColor textBase);
	UFUNCTION(BlueprintCallable) void SetTextSetAnimaiton(bool isTextAnimation);
	UFUNCTION(BlueprintCallable) void SetTextAnimationTime(float time);
	UFUNCTION(BlueprintCallable) void SetTextAnimationVelocity(FVector2D speed);

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	float curTime = 0;
	FVector2D moveSpeed = 0;
	float deleteTime = 0;
	bool isAnimation = false;
	float BaseAlpha = 1;
	FVector BaseColor;
};
