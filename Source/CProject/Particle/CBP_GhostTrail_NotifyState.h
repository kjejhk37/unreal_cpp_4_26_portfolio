// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Particle/CBP_GhostTrail.h"
#include "CBP_GhostTrail_NotifyState.generated.h"


UCLASS()
class CPROJECT_API UCBP_GhostTrail_NotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UCBP_GhostTrail_NotifyState();

	virtual FString GetNotifyName_Implementation() const override;
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;
	virtual void NotifyTick(class USkeletalMeshComponent * MeshComp, class UAnimSequenceBase * Animation, float FrameDeltaTime)override;
	
public:
	// Trail나타나는 빈도(trailInterval 마다 잔상이 남음)
	UPROPERTY(EditAnywhere) float trailInterval = 0.15f;
	
	// Trail이 사라지는 시간
	UPROPERTY(EditAnywhere) float trailTime = 0.5f;

	// 사용할 Trail 블루프린트
	UPROPERTY(EditAnywhere) TSubclassOf<ACBP_GhostTrail> GhostTrailClass;

private:
	float curTime;


};
