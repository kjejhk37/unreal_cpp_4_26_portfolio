// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/NS_InteractionObject/CBP_NS_InteractionObject.h"
#include "CBP_RemoteObject.generated.h"


UCLASS()
class CPROJECT_API ACBP_RemoteObject : public ACBP_NS_InteractionObject
{
	GENERATED_BODY()

public:
	ACBP_RemoteObject();
public:
	// CBPI_Interaction 인터페이스
	void Interaction(AActor* const InteractionActor, bool& Success, AActor*& ResultActor) override;
	void SetLock(bool inLock) override;

	UFUNCTION(BlueprintCallable) virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite,EditInstanceOnly, Category = "Set") TArray<AActor*> RemoteTargetActors;

	UFUNCTION(BlueprintCallable) void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	TArray<AActor*> overlapedActors;
};
