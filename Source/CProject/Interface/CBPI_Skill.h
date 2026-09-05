// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CBPI_Skill.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCBPI_Skill : public UInterface
{
	GENERATED_BODY()
};

class CPROJECT_API ICBPI_Skill
{
	GENERATED_BODY()

public:
	virtual void Play(bool const InSuccess, bool& Success) PURE_VIRTUAL(ICBPI_Skill::Play, return;);
	virtual void SetSpawn(AActor* centerActor) PURE_VIRTUAL(ICBPI_Skill::SetSpawn, return;);

	virtual void SetStart() PURE_VIRTUAL(ICBPI_Skill::SetStart, return;);
	virtual void SetEnd() PURE_VIRTUAL(ICBPI_Skill::SetEnd, return;);

	virtual void Attack() PURE_VIRTUAL(ICBPI_Skill::Attack, return;);


};

