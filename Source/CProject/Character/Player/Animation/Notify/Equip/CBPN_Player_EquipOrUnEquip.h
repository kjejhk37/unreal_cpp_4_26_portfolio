// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifies/AnimNotify_PlayMontageNotify.h"
#include "CBPN_Player_EquipOrUnEquip.generated.h"


UCLASS()
class CPROJECT_API UCBPN_Player_EquipOrUnEquip : public UAnimNotify_PlayMontageNotify
{
	GENERATED_BODY()

public:
	UCBPN_Player_EquipOrUnEquip();

	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};
