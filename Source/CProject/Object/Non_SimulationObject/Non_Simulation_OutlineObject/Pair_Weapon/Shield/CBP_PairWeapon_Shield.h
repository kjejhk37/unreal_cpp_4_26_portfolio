// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/Pair_Weapon/CBP_PairWeapon.h"
#include "CBP_PairWeapon_Shield.generated.h"

UCLASS()
class CPROJECT_API ACBP_PairWeapon_Shield : public ACBP_PairWeapon
{
	GENERATED_BODY()

public:
	ACBP_PairWeapon_Shield();
	void OnConstruction(const FTransform& Transform) override;
protected:
	void Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType) override;
	virtual void BeginPlay() override;

public:
	void Activate(bool InSuccess, bool& OutSuccess) override;
	void DeActivate(bool InSuccess, bool& OutSuccess) override;

	UFUNCTION(BlueprintCallable, Category = "Guard") void CheckGuard(AActor* const otherActor, bool& canGuard);

protected:
	UPROPERTY(VisibleAnywhere) UParticleSystemComponent* particleSystem;
	UPROPERTY(VisibleAnywhere) UShapeComponent* ShieldComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Type") ECollisionType ShieldCollisionType = ECollisionType::Box;


};
