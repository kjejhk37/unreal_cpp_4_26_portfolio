// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/NS_InteractionObject/CBP_NS_InteractionObject.h"
#include "CBP_AnimationObject.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API ACBP_AnimationObject : public ACBP_NS_InteractionObject
{
	GENERATED_BODY()
	
public:
	ACBP_AnimationObject();
	void OnConstruction(const FTransform& Transform) override;
	UFUNCTION(BlueprintCallable) virtual void BeginPlay() override;
protected:
	void Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType) override;

	void Interaction(AActor* const InteractionActor, bool& Success, AActor*& ResultActor) override;
	void SetLock(bool inLock) override;

public:
	void OpenKey(AActor* keyObject, bool& Success)override;

protected:
	UPROPERTY(VisibleAnywhere) UChildActorComponent* parkourAnimationObject;
	UPROPERTY(VisibleAnywhere) USceneComponent* center;

public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite,Category = "Set") FRotator ActorEndRotator;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite,Category = "Set") FTransform StartTransform;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite,Category = "Set") FTransform EndTransform;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite,Category = "Set") float playTime = 1;

	FRotator ActorStartRotator;
	FRotator TempActorEndRotator;
protected:
	UPROPERTY()
		class UTimelineComponent* AnimationTimeLine;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
		class UCurveFloat* BlendCurveOnAnimation;

private:
	UFUNCTION()
		void Animation(float const Alpha);

	bool isPlay = false;

	bool isOnceBind = false;
protected:
	bool canOpen = true;

public:
	void SetBeginPlay();

};
