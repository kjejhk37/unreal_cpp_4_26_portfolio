// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Quest/Sub_Quest/CBP_Sub_QuestActor.h"
#include "CBP_Arrive_Sub_QuestActor.generated.h"


UCLASS()
class CPROJECT_API ACBP_Arrive_Sub_QuestActor : public ACBP_Sub_QuestActor
{
	GENERATED_BODY()

public:
	ACBP_Arrive_Sub_QuestActor();

	void StartQuest() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere) class UBoxComponent* ArriveCollision;
	UPROPERTY(VisibleAnywhere) class UParticleSystemComponent* particle;

	UFUNCTION(BlueprintCallable) void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UPROPERTY(EditDefaultsOnly,Category = "Set") FVector QuestLocation = FVector();
	UPROPERTY(EditDefaultsOnly,Category = "Set") FVector CollisionExtent = FVector(100,100,100);


};
