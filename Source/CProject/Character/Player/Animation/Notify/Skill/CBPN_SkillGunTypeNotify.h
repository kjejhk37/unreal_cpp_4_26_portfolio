// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Skill/Spawn_Skill/Spawn_Gun/CBP_Spawn_Gun_Skill.h"
#include "Struct/SCharacter.h"
#include "CBPN_SkillGunTypeNotify.generated.h"

UCLASS()
class CPROJECT_API UCBPN_SkillGunTypeNotify : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	UCBPN_SkillGunTypeNotify();

	virtual FString GetNotifyName_Implementation() const override;
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;
	virtual void NotifyTick(class USkeletalMeshComponent * MeshComp, class UAnimSequenceBase * Animation, float FrameDeltaTime)override;

public:
	UPROPERTY(EditAnywhere, Category = "SkillClass") TSubclassOf<ACBP_Spawn_Gun_Skill> skillClass;

	UPROPERTY(EditAnywhere, Category = "Setting") FVector LocalStartPos;
	UPROPERTY(EditAnywhere, Category = "Setting") FVector LocalEndPos;

	UPROPERTY(EditAnywhere, Category = "Setting") float DelayTime;
	UPROPERTY(EditAnywhere, Category = "Setting") int AttackCount;
	UPROPERTY(EditAnywhere, Category = "Setting") float AttackCoolTime;
	UPROPERTY(EditAnywhere, Category = "Setting") float AttackLenght;
	UPROPERTY(EditAnywhere, Category = "Setting") float EndPlaySpeed;

	UPROPERTY(EditAnywhere, Category = "Setting") F_Hp_Update_Value damage;
	UPROPERTY(EditAnywhere, Category = "Setting") EAttackType attackType;
	UPROPERTY(EditAnywhere, Category = "Setting") EAttackHitType attackHitType;
	UPROPERTY(EditAnywhere, Category = "Setting") FVector pushVector = FVector(1, 0, 0);


	TMap<AActor*, ACBP_Skill*> skills;
//	UPROPERTY() ACBP_Skill* skill;

};
