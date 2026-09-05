// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifies/AnimNotify_PlayMontageNotify.h"
#include "CBPN_Player_WeaponMontagePlay.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API UCBPN_Player_WeaponMontagePlay : public UAnimNotify_PlayMontageNotify
{
	GENERATED_BODY()


public:
	UCBPN_Player_WeaponMontagePlay();

	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
public:
	UPROPERTY(EditAnywhere) int ShotNum = 1;
	UPROPERTY(EditAnywhere) UAnimMontage* GunMontage;

};
