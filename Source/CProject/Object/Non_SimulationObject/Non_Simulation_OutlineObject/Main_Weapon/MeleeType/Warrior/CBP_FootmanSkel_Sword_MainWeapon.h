// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/Main_Weapon/MeleeType/CBP_Melee_MainWeapon.h"
#include "CBP_FootmanSkel_Sword_MainWeapon.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API ACBP_FootmanSkel_Sword_MainWeapon : public ACBP_Melee_MainWeapon
{
	GENERATED_BODY()

public:
	ACBP_FootmanSkel_Sword_MainWeapon();

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	
protected:
	UFUNCTION() void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;

};

