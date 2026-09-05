// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Skill/CBP_Skill.h"
#include "Skill/ProjectileType/CBP_SimpleProjectileSkill.h"
#include "Struct/SCharacter.h"
#include "CBPN_SimpleProjectile_Notify.generated.h"


UCLASS()
class CPROJECT_API UCBPN_SimpleProjectile_Notify : public UAnimNotifyState
{
	GENERATED_BODY()
	

public:
	UCBPN_SimpleProjectile_Notify();

	virtual FString GetNotifyName_Implementation() const override;
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;
	virtual void NotifyTick(class USkeletalMeshComponent * MeshComp, class UAnimSequenceBase * Animation, float FrameDeltaTime)override;

public:
	UPROPERTY(EditAnywhere, Category = "SkillClass") TSubclassOf<ACBP_SimpleProjectileSkill> skillClass;

	UPROPERTY(EditAnywhere, Category = "Setting") FVector LocalStartPos;
	UPROPERTY(EditAnywhere, Category = "Setting") FVector LocalEndPos;

	UPROPERTY(EditAnywhere, Category = "Setting") float DelayTime;
	UPROPERTY(EditAnywhere, Category = "Setting") FVector EndPointer;
	UPROPERTY(EditAnywhere, Category = "Setting") TSubclassOf<AActor> MeshType;
	UPROPERTY(EditAnywhere, Category = "Setting") float MoveSpeed;

	UPROPERTY(EditAnywhere, Category = "Setting") F_Hp_Update_Value damage;
	UPROPERTY(EditAnywhere, Category = "Setting") EAttackType attackType;
	UPROPERTY(EditAnywhere, Category = "Setting") EAttackHitType attackHitType;
	UPROPERTY(EditAnywhere, Category = "Setting") FVector pushVector = FVector(1, 0, 0);

//	UPROPERTY() ACBP_Skill* skill;
	TMap<AActor*, ACBP_Skill*> skills;

};
