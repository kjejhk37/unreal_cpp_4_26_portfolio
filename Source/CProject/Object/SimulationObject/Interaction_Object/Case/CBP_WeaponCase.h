// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/SimulationObject/Interaction_Object/CBP_Interaction_Object.h"
#include "Components/ChildActorComponent.h"
#include "CBP_WeaponCase.generated.h"


UCLASS()
class CPROJECT_API ACBP_WeaponCase : public ACBP_Interaction_Object
{
	GENERATED_BODY()
	
public:
	ACBP_WeaponCase();
	void OnConstruction(const FTransform& Transform) override;

protected:
	virtual void BeginPlay() override;
	void Set_Simul_ComponentsBase(EMeshType newMeshType, ESimulationType newSimulationType, ECollisionType newInteractionType)override;

public:
	// CBPI_Interaction 인터페이스
	void Interaction(AActor* const InteractionActor, bool& Success, AActor*& ResultActor) override;
	void SetDropping(FVector newLocation, FVector impulseVector, float power);

public:
	UPROPERTY(VisibleAnywhere) UChildActorComponent* mainWeaponSocket;
	UPROPERTY(VisibleAnywhere) UChildActorComponent* pairWeaponSocket;



};
