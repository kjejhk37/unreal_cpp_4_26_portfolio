#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/EngineTypes.h"

#include "Character/AICharacter/CBP_AICharacter.h"

#include "SInteraction.generated.h"


USTRUCT(BlueprintType)
struct F_SpawnMonsterData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TSubclassOf<ACBP_AICharacter> SpawnChatracter;
	UPROPERTY(EditAnywhere) FVector SpawnPos;
	UPROPERTY(EditAnywhere) FRotator SpawnRotator;
};

USTRUCT(BlueprintType)
struct F_SpawnMonsterStageData
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere) TArray<F_SpawnMonsterData> eachStageDatas;
};
