// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AICharacter/CBP_AICharacter.h"
#include "Particle/CBP_GhostTrail.h"
#include "CBP_WarLoadSkel.generated.h"


UCLASS()
class CPROJECT_API ACBP_WarLoadSkel : public ACBP_AICharacter
{
	GENERATED_BODY()

public:
	ACBP_WarLoadSkel();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void PossessedBy(AController* NewController) override;

	void Action() override;
	void EquipOrUnEquip() override;

	void ActionDropping(bool& Success) override;

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "WeaponClass") TSubclassOf<ACBP_MainWeapon> mainWeaponClass;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "WeaponClass") TSubclassOf<ACBP_PairWeapon> pairWeaponClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GhostTrail") TSubclassOf<ACBP_GhostTrail> ghostTrailClass;


private:
	float curTime;
	float trailTime = 1.0f;
	float trailInterval = 0.15f;


};
