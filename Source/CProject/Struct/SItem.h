#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/EngineTypes.h"
#include "Enums/EItem.h"
#include "SItem.generated.h"

USTRUCT(BlueprintType)
struct F_ItemInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) EItemName itemName;

	UPROPERTY(EditAnywhere) float updateValue = 0;
	UPROPERTY(EditAnywhere) int updateCount = 1;
	UPROPERTY(EditAnywhere) int curUpdateTick = 0;
	UPROPERTY(EditAnywhere) int maxUpdateTick = 0;
};