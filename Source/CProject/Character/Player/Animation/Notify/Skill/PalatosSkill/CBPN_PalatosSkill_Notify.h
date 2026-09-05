// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Skill/SimpleSkill/CBP_Palatos_Skill.h"
#include "CBPN_PalatosSkill_Notify.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API UCBPN_PalatosSkill_Notify : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	UCBPN_PalatosSkill_Notify();

	virtual FString GetNotifyName_Implementation() const override;
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;
	virtual void NotifyTick(class USkeletalMeshComponent * MeshComp, class UAnimSequenceBase * Animation, float FrameDeltaTime)override;

public:
	UPROPERTY(EditAnywhere, Category = "SkillClass") TSubclassOf<ACBP_Palatos_Skill> skillClass;

	UPROPERTY(EditAnywhere, Category = "Setting") FVector LocalStartPos;
	UPROPERTY(EditAnywhere, Category = "Setting") FVector LocalEndPos;

	UPROPERTY(EditAnywhere, Category = "Setting") float DelayTime;
	UPROPERTY(EditAnywhere, Category = "Setting") float MoveSpeed;

	UPROPERTY(EditAnywhere, Category = "Setting") int PalatosNum = 1;
	UPROPERTY(EditAnywhere, Category = "Setting") float PalatosLenght = 100;

	UPROPERTY(EditAnywhere, Category = "Setting") TSubclassOf<ACBP_SimpleProjectileSkill> attackSkillClass;
	UPROPERTY(EditAnywhere, Category = "Setting") UAnimMontage* SetEndMontage;

	UPROPERTY(EditAnywhere, Category = "Setting") F_Hp_Update_Value damage;
	UPROPERTY(EditAnywhere, Category = "Setting") EAttackType attackType;
	UPROPERTY(EditAnywhere, Category = "Setting") EAttackHitType attackHitType;
	UPROPERTY(EditAnywhere, Category = "Setting") FVector pushVector = FVector(1, 0, 0);

	UPROPERTY(EditAnywhere, Category = "Setting") ESkillType skillType = ESkillType::Skill_1;

	UPROPERTY(EditAnywhere, Category = "Setting") bool isChargeType = true;


	UPROPERTY() ACBP_Skill* skill;
};
