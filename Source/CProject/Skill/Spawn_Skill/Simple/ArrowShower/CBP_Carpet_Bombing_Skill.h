// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/Spawn_Skill/Simple/ArrowShower/CBP_ArrowShower_Skill.h"
#include "CBP_Carpet_Bombing_Skill.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API ACBP_Carpet_Bombing_Skill : public ACBP_ArrowShower_Skill
{
	GENERATED_BODY()

public:
	ACBP_Carpet_Bombing_Skill();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Set") float ArrowFrequencyTime = 0.1f;
	UPROPERTY(EditDefaultsOnly, Category = "Set") int Count = 10;
	UPROPERTY(EditDefaultsOnly, Category = "Set")  TSubclassOf<ACBP_ArrowShower_Arrow_Spawn> skillClass;
	UPROPERTY(EditDefaultsOnly, Category = "Set")  FVector skillScale = FVector(1, 1, 1);

	UPROPERTY(EditDefaultsOnly, Category = "Set")  float XLenght = 50;
	UPROPERTY(EditDefaultsOnly, Category = "Set")  float YLenght = 50;

	UPROPERTY(EditDefaultsOnly, Category = "Set")  int LineNum = 1;


};
