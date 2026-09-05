#include "Logger.h"

DEFINE_LOG_CATEGORY(GPC)

int32  const Logger::DefaultKey = INDEX_NONE;
float  const Logger::DefaultDuration = 5.0f;
FColor const Logger::DefaultColor = FColor::Red;

void Logger::Print(int32 const& Data, int32 const Key, float const Duration, FColor const Color)
{
	GEngine->AddOnScreenDebugMessage(Key, Duration, Color, FString::FromInt(Data));
}

void Logger::Print(float const& Data, int32 const Key, float const Duration, FColor const Color)
{
	GEngine->AddOnScreenDebugMessage(Key, Duration, Color, FString::SanitizeFloat(Data));
}

void Logger::Print(FString const& Data, int32 const Key, float const Duration, FColor const Color)
{
	GEngine->AddOnScreenDebugMessage(Key, Duration, Color, Data);
}

void Logger::Print(FVector const& Data, int32 const Key, float const Duration, FColor const Color)
{
	GEngine->AddOnScreenDebugMessage(Key, Duration, Color, Data.ToString());
}

void Logger::Print(FRotator const& Data, int32 const Key, float const Duration, FColor const Color)
{
	GEngine->AddOnScreenDebugMessage(Key, Duration, Color, Data.ToString());
}

void Logger::Print(UObject* const& Data, int32 const Key, float const Duration, FColor const Color)
{
	GEngine->AddOnScreenDebugMessage(Key, Duration, Color, Data->GetFName().ToString());
}

void Logger::Log(int32 const& Data)
{
	UE_LOG(GPC, Display, TEXT("%i"), Data);
}

void Logger::Log(float const& Data)
{
	UE_LOG(GPC, Display, TEXT("%f"), Data);
}

void Logger::Log(FString const& Data)
{
	UE_LOG(GPC, Display, TEXT("%s"), *Data);
}

void Logger::Log(FVector const& Data)
{
	UE_LOG(GPC, Display, TEXT("%s"), *Data.ToString());
}

void Logger::Log(FRotator const& Data)
{
	UE_LOG(GPC, Display, TEXT("%s"), *Data.ToString());
}

void Logger::Log(UObject* const& Data)
{
	UE_LOG(GPC, Display, TEXT("%s"), *Data->GetFName().ToString());
}

