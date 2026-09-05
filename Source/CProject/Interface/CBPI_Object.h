// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enums/EObject.h"
#include "CBPI_Object.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCBPI_Object : public UInterface
{
	GENERATED_BODY()
};

class CPROJECT_API ICBPI_Object
{
	GENERATED_BODY()

public:
	virtual void Set_Simul_ComponentsBase(EMeshType newMeshType, ESimulationType newSimulationType, ECollisionType newInteractionType) PURE_VIRTUAL(ICBPI_Simulation::SetComponentsBase, return;)
	virtual void Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType) PURE_VIRTUAL(ICBPI_Simulation::SetComponentsBase, return;)

};
