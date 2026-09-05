// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/Spawn_Skill/Simple/AnimationType/CBP_AnimationType_SkillType.h"
#include "CBP_Dual_AnimationSkill.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API ACBP_Dual_AnimationSkill : public ACBP_AnimationType_SkillType
{
	GENERATED_BODY()

public:
	ACBP_Dual_AnimationSkill();

protected:
	virtual void BeginPlay() override;


protected:
	UFUNCTION() void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)override;


	
};
