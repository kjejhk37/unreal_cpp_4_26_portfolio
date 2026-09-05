// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CBPI_Interaction.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCBPI_Interaction : public UInterface
{
	GENERATED_BODY()
};


class CPROJECT_API ICBPI_Interaction
{
	GENERATED_BODY()

public:

	virtual void Interaction(AActor* const InteractionActor, bool& Success , AActor*& ResultActor)	PURE_VIRTUAL(ICBPI_Interaction::Interaction, return;);
	virtual void SetLock(bool inLock)																PURE_VIRTUAL(ICBPI_Interaction::SetLock, return;);

	virtual void OpenKey(AActor* keyObject, bool& Success)											PURE_VIRTUAL(ICBPI_Interaction::OpenKey, return;);
	virtual void SetKey(AActor* keyObject)															PURE_VIRTUAL(ICBPI_Interaction::SetKey, return;);
	virtual void IsLockedKey(AActor* keyObject, bool& LockedKey)									PURE_VIRTUAL(ICBPI_Interaction::IsLockedKey, return;);
	virtual void SetQuest(AActor* QuestActor)														PURE_VIRTUAL(ICBPI_Interaction::SetQuest, return;);


};
