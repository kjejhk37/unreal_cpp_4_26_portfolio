// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AICharacter/CBP_AICharacter.h"
#include "CBP_SorcererSkel.generated.h"


UCLASS()
class CPROJECT_API ACBP_SorcererSkel : public ACBP_AICharacter
{
	GENERATED_BODY()

public:
	ACBP_SorcererSkel();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void PossessedBy(AController* NewController) override;

	void Action() override;
	void EquipOrUnEquip() override;

	void SetDeleteSpawnedActor(AActor* InDeleteSpawnedActor)override;

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "WeaponClass") TSubclassOf<ACBP_MainWeapon> mainWeaponClass;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "WeaponClass") TSubclassOf<ACBP_PairWeapon> pairWeaponClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Set") class UParticleSystem* DeleteSpawnedActorParticle;

};
