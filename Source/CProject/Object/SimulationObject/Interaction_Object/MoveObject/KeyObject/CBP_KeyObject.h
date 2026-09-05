// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../CBP_Interaction_Object.h"
#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/NS_InteractionObject/Animation_Object/CBP_AnimationObject.h"
#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/NS_InteractionObject/Animation_Object/Remote/CBP_RemoteObject.h"
#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/NS_InteractionObject/PortalObject/CBP_PortalObject.h"

#include "Interface/CBPI_Interaction.h"

#include "CBP_KeyObject.generated.h"

UCLASS()
class CPROJECT_API ACBP_KeyObject : public ACBP_Interaction_Object
{
	GENERATED_BODY()

public:
	ACBP_KeyObject();
	void OnConstruction(const FTransform& Transform) override;
	//	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
protected:
	void Set_Simul_ComponentsBase(EMeshType newMeshType, ESimulationType newSimulationType, ECollisionType newInteractionType)override;

	void Interaction(AActor* const InteractionActor, bool& Success, AActor*& ResultActor) override;
	void SetLock(bool inLock) override;

public:

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category = "Set") TArray<AActor*> WillLockActors;


};
