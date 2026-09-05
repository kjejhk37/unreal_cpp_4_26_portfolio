// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBP_InterfaceActor.generated.h"

UCLASS()
class CPROJECT_API ACBP_InterfaceActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBP_InterfaceActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Set") FText Line_1_Text;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Set") FText Line_2_Text;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Set") FText Line_3_Text;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Set") FText Line_4_Text;

};
