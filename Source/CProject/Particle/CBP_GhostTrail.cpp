// Fill out your copyright notice in the Description page of Project Settings.


#include "Particle/CBP_GhostTrail.h"
#include "Components/PoseableMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "Macro/MyMacro.h"
#include "Logger/Logger.h"

ACBP_GhostTrail::ACBP_GhostTrail()
{
	PrimaryActorTick.bCanEverTick = true;

	CreateDefaultSubobjectAuto(TrailAlphaTimeline);
	SceneRootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));

	RootComponent = SceneRootComp;

	PoseableMeshComp = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("PoseableMeshComp"));
	PoseableMeshComp->SetupAttachment(RootComponent);

}

void ACBP_GhostTrail::BeginPlay()
{
	Super::BeginPlay();
	
}


void ACBP_GhostTrail::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

//	OpacityTimeline.TickTimeline(DeltaTime);
	curTime += DeltaTime;
	float value = curTime * inverseTrailTime;
	DynamicMatInstance->SetScalarParameterValue(ScalarParameterName, 1 - value);
	
	if (curTime >= trailTime)
	{
		DestroyActor(this);
	}
}

void ACBP_GhostTrail::BeginGhostTrailEffect()
{
	if (TrailAlphaCurve && PoseCharacter && GhostTrailMaterial)
	{
		// 메시 복사
		PoseableMeshComp->SetSkeletalMesh(PoseCharacter->GetMesh()->SkeletalMesh);
		// 포즈 복사
		PoseableMeshComp->CopyPoseFromSkeletalComponent(PoseCharacter->GetMesh());

		// Relative 위치 조정
		PoseableMeshComp->SetRelativeLocation(PoseCharacter->GetMesh()->GetRelativeLocation());
		PoseableMeshComp->SetRelativeRotation(PoseCharacter->GetMesh()->GetRelativeRotation());

		// Actor 위치 조정
		SetActorLocation(PoseCharacter->GetActorLocation());
		SetActorRotation(PoseCharacter->GetActorRotation());

		// Material 셋팅
		DynamicMatInstance = UMaterialInstanceDynamic::Create(GhostTrailMaterial, this);
		TArray <FSkeletalMaterial> materials = PoseCharacter->GetMesh()->SkeletalMesh->Materials;


		for (int32 Index = 0; Index != materials.Num(); ++Index)
		{
			PoseableMeshComp->SetMaterial(Index, DynamicMatInstance);
		}

		// 타임라인 셋팅 (투명도 조절) -> 난 안됨
		FOnTimelineFloat OnTrailAlpha;
		OnTrailAlpha.BindDynamic(this, &ThisClass::HandleTimelineUpdate);
		TrailAlphaTimeline->AddInterpFloat(TrailAlphaCurve, OnTrailAlpha);

		if (trailTime == 0)
		{
			TrailAlphaTimeline->SetPlayRate(1);
			inverseTrailTime = 1;
		}
		else
		{
			TrailAlphaTimeline->SetPlayRate(1 / trailTime);
			inverseTrailTime = 1 / trailTime;
		}

		FOnTimelineEvent endEvent;
		endEvent.BindDynamic(this, &ThisClass::HandleTimelineFinished);
		TrailAlphaTimeline->SetTimelineFinishedFunc(endEvent);

		TrailAlphaTimeline->Play();
		curTime = 0;
	}
}

void ACBP_GhostTrail::HandleTimelineUpdate(float Value)
{
	DynamicMatInstance->SetScalarParameterValue(ScalarParameterName,1 - Value);
}

void ACBP_GhostTrail::HandleTimelineFinished()
{
	DestroyActor(this);
}
