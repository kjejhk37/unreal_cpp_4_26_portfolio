// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifies/AnimNotify_PlayMontageNotify.h"
#include "Skill/Spawn_Skill/Simple/Bullet/CBP_BulletType_Skill.h"
#include "CBPN_Bullet_Shot_Notify.generated.h"

UCLASS()
class CPROJECT_API UCBPN_Bullet_Shot_Notify : public UAnimNotify_PlayMontageNotify
{
	GENERATED_BODY()

public:
	UCBPN_Bullet_Shot_Notify();

	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

public:
	UPROPERTY(EditAnywhere) TSubclassOf<ACBP_BulletType_Skill> ShotClass;
	
	UPROPERTY(EditAnywhere, Category = "Socket") FName shotSocket = FName("ShotSocket");
	UPROPERTY(EditAnywhere, Category = "Socket") int ShotNum = 1;

	ACBP_Skill* skill;
	
};
