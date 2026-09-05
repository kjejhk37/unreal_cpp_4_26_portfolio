// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifies/AnimNotify_PlayMontageNotify.h"
#include "CBPN_Trail_Particle_Activate.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API UCBPN_Trail_Particle_Activate : public UAnimNotify_PlayMontageNotify
{
	GENERATED_BODY()
	
public:
	UCBPN_Trail_Particle_Activate();

	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

public:
	UPROPERTY(EditAnywhere, Category = "Setting") bool isActivate;
};
