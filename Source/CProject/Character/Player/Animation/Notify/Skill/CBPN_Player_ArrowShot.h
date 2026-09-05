// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifies/AnimNotify_PlayMontageNotify.h"
#include "Skill/Spawn_Skill/Simple/Arrow/CBP_Player_ArrowShot.h"
#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/Main_Weapon/BowType/CBP_BowMainWeapon.h"

#include "CBPN_Player_ArrowShot.generated.h"


UCLASS()
class CPROJECT_API UCBPN_Player_ArrowShot : public UAnimNotify_PlayMontageNotify
{
	GENERATED_BODY()
	
		

public:
	UCBPN_Player_ArrowShot();

	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
public:
	UPROPERTY(EditAnywhere) TSubclassOf<ACBP_Player_ArrowShot> arrowClass;

	UPROPERTY(EditAnywhere, Category = "Socket") FName shotReadySocket = FName("Bow_shotReadySocket");
	UPROPERTY(EditAnywhere, Category = "Socket") FName shotSocket = FName("Bow_shotSocket");
	UPROPERTY(EditAnywhere, Category = "Socket") FName trail_Start = FName("Trail_Start");
	UPROPERTY(EditAnywhere, Category = "Socket") FName trail_End = FName("Trail_End");

	ACBP_Skill* skill;

	
};
