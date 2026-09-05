// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AICharacter/CBP_AICharacter.h"
#include "Macro/IncludeMacro.h"

#include PairWeaponPath
#include MainWeaponPath

#include "CBP_FootmanSkel.generated.h"

UCLASS()
class CPROJECT_API ACBP_FootmanSkel : public ACBP_AICharacter
{
	GENERATED_BODY()

public:
	ACBP_FootmanSkel();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void PossessedBy(AController* NewController) override;

	void Action() override;
	void EquipOrUnEquip() override;

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "WeaponClass") TSubclassOf<ACBP_MainWeapon> mainWeaponClass;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "WeaponClass") TSubclassOf<ACBP_PairWeapon> pairWeaponClass;

};
