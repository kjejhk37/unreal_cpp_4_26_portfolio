// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Struct/SCharacter.h"
#include "CBPN_WeaponActivate_Notify.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API UCBPN_WeaponActivate_Notify : public UAnimNotifyState
{
	GENERATED_BODY()


public:
	UCBPN_WeaponActivate_Notify();

	virtual FString GetNotifyName_Implementation() const override;
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;
	virtual void NotifyTick(class USkeletalMeshComponent * MeshComp, class UAnimSequenceBase * Animation, float FrameDeltaTime)override;
	
	UPROPERTY(EditAnywhere) bool isMainWeapon = true;
	UPROPERTY(EditAnywhere) F_Hp_Update_Value damage;


};
