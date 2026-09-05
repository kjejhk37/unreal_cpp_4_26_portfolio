// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WCBP_QuestTextBase.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API UWCBP_QuestTextBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void MainQuestInterfaceUpdate(FText text);
	void SubQuestInterfaceUpdate(TArray<FText> texts);


};
