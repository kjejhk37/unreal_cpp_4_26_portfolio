#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(GPC, Display, All)

class CPROJECT_API Logger
{
public:
	static int32  const DefaultKey;
	static float  const DefaultDuration;
	static FColor const DefaultColor;

	static void Print(int32    const& Data, int32 const Key = DefaultKey, float const Duration = DefaultDuration, FColor const Color = DefaultColor);
	static void Print(float    const& Data, int32 const Key = DefaultKey, float const Duration = DefaultDuration, FColor const Color = DefaultColor);
	static void Print(FString  const& Data, int32 const Key = DefaultKey, float const Duration = DefaultDuration, FColor const Color = DefaultColor);
	static void Print(FVector  const& Data, int32 const Key = DefaultKey, float const Duration = DefaultDuration, FColor const Color = DefaultColor);
	static void Print(FRotator const& Data, int32 const Key = DefaultKey, float const Duration = DefaultDuration, FColor const Color = DefaultColor);
	static void Print(UObject* const& Data, int32 const Key = DefaultKey, float const Duration = DefaultDuration, FColor const Color = DefaultColor);

	static void Log(int32    const& Data);
	static void Log(float    const& Data);
	static void Log(FString  const& Data);
	static void Log(FVector  const& Data);
	static void Log(FRotator const& Data);
	static void Log(UObject* const& Data);
};
