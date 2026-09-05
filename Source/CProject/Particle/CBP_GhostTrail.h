// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"

#include "CBP_GhostTrail.generated.h"

class UPoseableMeshComponent;
class UMaterialInterface;
class UMaterialInstanceDynamic;

UCLASS()
class CPROJECT_API ACBP_GhostTrail : public AActor
{
	GENERATED_BODY()
	
public:	

	ACBP_GhostTrail();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "GhostTrail") void BeginGhostTrailEffect();

protected:
	UFUNCTION() void HandleTimelineUpdate(float Value);
	UFUNCTION() void HandleTimelineFinished();
public:
	UPROPERTY() ACharacter* PoseCharacter;	 // 포즈를 취할 캐릭터의 주소값
	UPROPERTY(EditDefaultsOnly, Category = "Setting") float trailTime = 0.5f;	// 사라지는데 걸리는 시간

protected:
	// 포즈 가져오기 위한 Component
	UPROPERTY(VisibleAnywhere) UPoseableMeshComponent* PoseableMeshComp;

	// Actor의 기준점 -> Character의 경우 Yaw값을 -90 Z값을 -90 옮겨야해서 만든 것
	UPROPERTY(VisibleAnywhere) USceneComponent* SceneRootComp;

	// Material
	UPROPERTY(EditDefaultsOnly, Category = "Setting") UMaterialInterface* GhostTrailMaterial;

	// 투명도 조절에 쓸 값
	UPROPERTY(EditDefaultsOnly, Category = "Setting") FName ScalarParameterName = FName(TEXT("TrailAlpha"));
	// 타임라인에 쓸 Curve
	UPROPERTY(EditDefaultsOnly, Category = "Setting") UCurveFloat*  TrailAlphaCurve;

	// Alpha값 조절을 해줄 Timeline -> 안되면 Tick에서 조절이 가능함
	UPROPERTY() UTimelineComponent* TrailAlphaTimeline;
	// Material Instance 여기에 Material 복사해서 투명도 조절하는 것
	UPROPERTY() UMaterialInstanceDynamic* DynamicMatInstance;

	// Timeline이 안될 떄 Tick에서 계산하하면서 쓸 값들
	float inverseTrailTime;
	float curTime;

	/* 이를 기준으로 ParkourComponent처럼 Component를 만들어 On/Off기능을 넣으면 좀더 기깔나게 가능할 듯  */

};

