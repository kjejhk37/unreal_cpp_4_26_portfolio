// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Skill/CBP_Skill.h"
#include "Skill/Spawn_Skill/Simple/AnimationType/CBP_AnimationType_SkillType.h"
#include "Struct/SCharacter.h"
#include "CBPN_AnimationSkill_Notify.generated.h"

UCLASS()
class CPROJECT_API UCBPN_AnimationSkill_Notify : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	UCBPN_AnimationSkill_Notify();

	virtual FString GetNotifyName_Implementation() const override;
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;
	virtual void NotifyTick(class USkeletalMeshComponent * MeshComp, class UAnimSequenceBase * Animation, float FrameDeltaTime)override;

public:
	// 이거 Rotator다 없애도록 해야함
	
	UPROPERTY(EditAnywhere, Category = "SkillClass") TSubclassOf<ACBP_AnimationType_SkillType> skillClass;

	UPROPERTY(EditAnywhere, Category = "Setting") FVector centerStartPos;
	UPROPERTY(EditAnywhere, Category = "Setting") FVector centerEndPos;

	UPROPERTY(EditAnywhere, Category = "Setting") FVector MeshStartRelativeLocation;
	UPROPERTY(EditAnywhere, Category = "Setting") FRotator MeshStartRot;
	UPROPERTY(EditAnywhere, Category = "Setting") FVector MeshStartScale = FVector(1,1,1);

	UPROPERTY(EditAnywhere, Category = "Setting") FVector CenterStartLookVector;
	UPROPERTY(EditAnywhere, Category = "Setting") float CenterStartRoll;
	UPROPERTY(EditAnywhere, Category = "Setting") FRotator CenterEndRotator;

	UPROPERTY(EditAnywhere, Category = "Setting") FVector CenterStartScale = FVector(1, 1, 1);
	UPROPERTY(EditAnywhere, Category = "Setting") FVector CenterEndScale = FVector(1, 1, 1);

	UPROPERTY(EditAnywhere, Category = "Setting") float AnimationTime;
	UPROPERTY(EditAnywhere, Category = "Setting") float DelayTime;
	UPROPERTY(EditAnywhere, Category = "Setting") float DestroyTime;

	UPROPERTY(EditAnywhere, Category = "Setting") int AttackNumber;

	UPROPERTY(EditAnywhere, Category = "Setting") FName Trail_Start = FName("Center");
	UPROPERTY(EditAnywhere, Category = "Setting") FName Trail_End = FName("Trail_End");

	UPROPERTY(EditAnywhere, Category = "Setting") F_Hp_Update_Value damage;
	UPROPERTY(EditAnywhere, Category = "Setting") EAttackType attackType;
	UPROPERTY(EditAnywhere, Category = "Setting") EAttackHitType attackHitType;
	UPROPERTY(EditAnywhere, Category = "Setting") FVector pushVector = FVector(1, 0, 0);



//	UPROPERTY() ACBP_Skill* skill;
	TMap<AActor*, ACBP_Skill*> skills;

};
