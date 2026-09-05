// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Skill/Spawn_Skill/Simple/Arrow/CBP_ArrowShot.h"
#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/Main_Weapon/BowType/CBP_BowMainWeapon.h"

#include "CBPN_ArcherSkel_ShotArrow.generated.h"


UCLASS()
class CPROJECT_API UCBPN_ArcherSkel_ShotArrow : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UCBPN_ArcherSkel_ShotArrow();

	virtual FString GetNotifyName_Implementation() const override;
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;
	virtual void NotifyTick(class USkeletalMeshComponent * MeshComp, class UAnimSequenceBase * Animation, float FrameDeltaTime)override;
	
public:
	UPROPERTY(EditAnywhere) TSubclassOf<ACBP_ArrowShot> arrowClass;

	UPROPERTY(EditAnywhere , Category = "Socket") FName shotReadySocket = FName("Bow_shotReadySocket");
	UPROPERTY(EditAnywhere, Category = "Socket") FName shotSocket = FName("Bow_shotSocket");
	UPROPERTY(EditAnywhere, Category = "Socket") FName trail_Start = FName("Trail_Start");
	UPROPERTY(EditAnywhere, Category = "Socket") FName trail_End = FName("Trail_End");

	UPROPERTY(EditAnywhere, Category = "Set") float SetTime = 0;
	
private:
//	ACBP_Skill* skill;
	float curTime = 0;

	TMap<AActor*, ACBP_Skill*> skills;
	

};
