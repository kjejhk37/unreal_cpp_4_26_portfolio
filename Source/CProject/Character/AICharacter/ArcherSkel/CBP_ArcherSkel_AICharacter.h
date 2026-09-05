// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AICharacter/CBP_AICharacter.h"
#include "Macro/IncludeMacro.h"

#include MainWeaponPath

#include "CBP_ArcherSkel_AICharacter.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API ACBP_ArcherSkel_AICharacter : public ACBP_AICharacter
{
	GENERATED_BODY()

public:
	ACBP_ArcherSkel_AICharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void PossessedBy(AController* NewController) override;

	void Action() override;
	void EquipOrUnEquip() override;

protected:
	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* Quiver;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "WeaponClass") TSubclassOf<ACBP_MainWeapon> mainWeaponClass;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "WeaponClass") TSubclassOf<ACBP_PairWeapon> pairWeaponClass;

};
