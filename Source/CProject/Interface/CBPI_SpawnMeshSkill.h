// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enums/EObject.h"
#include "CBPI_SpawnMeshSkill.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCBPI_SpawnMeshSkill : public UInterface
{
	GENERATED_BODY()
};

class CPROJECT_API ICBPI_SpawnMeshSkill
{
	GENERATED_BODY()

public:
	virtual void SetMesh(EMeshType newMeshType) PURE_VIRTUAL(ICBPI_SpawnMeshSkill::SetMesh, return;);

};
