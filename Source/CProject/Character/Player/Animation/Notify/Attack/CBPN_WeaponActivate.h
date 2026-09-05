// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifies/AnimNotify_PlayMontageNotify.h"
#include "CBPN_WeaponActivate.generated.h"


UCLASS()
class CPROJECT_API UCBPN_WeaponActivate : public UAnimNotify_PlayMontageNotify
{
	GENERATED_BODY()
	
public:
	UCBPN_WeaponActivate();

	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

public:
	UPROPERTY(EditAnywhere, Category = "Setting") bool isPairWeapon;
	UPROPERTY(EditAnywhere,  Category = "Setting") bool isActivate;

};
