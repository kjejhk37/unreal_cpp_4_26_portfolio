// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/NS_InteractionObject/Animation_Object/CBP_AnimationObject.h"
#include "CBP_ChestBox.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API ACBP_ChestBox : public ACBP_AnimationObject
{
	GENERATED_BODY()
		
public:
	ACBP_ChestBox();

	virtual void BeginPlay() override;

	void Interaction(AActor* const InteractionActor, bool& Success, AActor*& ResultActor)override;

public:
	UPROPERTY(EditAnywhere,Category = "Set") TArray<TSubclassOf<AActor>> contents;

protected:
	UFUNCTION() void OpenEnd();

	UFUNCTION() void DeleteBox();

};
