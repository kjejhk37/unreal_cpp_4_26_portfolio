// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Character/CBP_Character.h"

#include "WCBP_ProgressBarBase.generated.h"


UCLASS()
class CPROJECT_API UWCBP_ProgressBarBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable) void UpdateProgressBar(float curHp, float maxHp);

public:

};
