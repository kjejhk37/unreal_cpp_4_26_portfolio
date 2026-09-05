// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Skill/CBP_Skill.h"
#include "Skill/Spawn_Skill/Simple/Homing/CBP_Spawn_HomingSkill.h"
#include "Enums/EWeapon.h"
#include "Struct/SCharacter.h"
#include "CBPN_HomingSkill_Notify.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API UCBPN_HomingSkill_Notify : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UCBPN_HomingSkill_Notify();

	virtual FString GetNotifyName_Implementation() const override;
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;
	virtual void NotifyTick(class USkeletalMeshComponent * MeshComp, class UAnimSequenceBase * Animation, float FrameDeltaTime)override;

public:
	UPROPERTY(EditAnywhere, Category = "SkillClass") TSubclassOf<ACBP_Spawn_HomingSkill> skillClass;

	UPROPERTY(EditAnywhere, Category = "Setting") FVector CenterStartPos;
	UPROPERTY(EditAnywhere, Category = "Setting") FVector CenterEndPos;

	UPROPERTY(EditAnywhere, Category = "Setting") float centerStartRotRoll;
	UPROPERTY(EditAnywhere, Category = "Setting") FVector localLookVector;

	UPROPERTY(EditAnywhere, Category = "Setting") FName Trail_Start = FName("Trail_Left");
	UPROPERTY(EditAnywhere, Category = "Setting") FName Trail_End = FName("Trail_Right");

	UPROPERTY(EditAnywhere, Category = "Setting") float DelayTime;
	UPROPERTY(EditAnywhere, Category = "Setting") float SetTargetTime = 1;
	UPROPERTY(EditAnywhere, Category = "Setting") float MoveSpeed;

	UPROPERTY(EditAnywhere, Category = "Setting") EHomingSkillType homingType;

	UPROPERTY(EditAnywhere, Category = "Setting") F_Hp_Update_Value damage;
	UPROPERTY(EditAnywhere, Category = "Setting") EAttackType attackType;
	UPROPERTY(EditAnywhere, Category = "Setting") EAttackHitType attackHitType;
	UPROPERTY(EditAnywhere, Category = "Setting") FVector pushVector = FVector(1, 0, 0);

	TMap<AActor*, ACBP_Skill*> skills;
//	UPROPERTY() ACBP_Skill* skill;
	
};
