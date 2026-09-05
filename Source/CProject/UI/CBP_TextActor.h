// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBP_TextActor.generated.h"

UCLASS()
class CPROJECT_API ACBP_TextActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBP_TextActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere) class USceneComponent* center;
	UPROPERTY(VisibleAnywhere) class UWidgetComponent* text;

	UFUNCTION(BlueprintCallable) void SetTextBox(
		FString InString,
		FVector IntextBaseColor = FVector(1,1,1),
		FVector2D Inpos = FVector2D(0,0),
		float IntextBaseAlpha = 1,
		bool InisTextAnimation = true,
		float Intime = 1,
		FVector2D Inspeed = FVector2D(0,-100)
	);

	UFUNCTION(BlueprintCallable) void SetTextFont(float fontSize = 24);
	UFUNCTION(BlueprintCallable) void SetTextOutlineFont(float fontSize = 1);

	UFUNCTION(BlueprintCallable) void DestoryThisActor();
private:


};
