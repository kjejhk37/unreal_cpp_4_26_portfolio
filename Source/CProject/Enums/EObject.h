#pragma once

UENUM(BlueprintType)
enum class ECollisionType : uint8
{
	None,
	Box,
	Sphere,
	Capsule
};

UENUM(BlueprintType)
enum class ESimulationType : uint8
{
	None,
	Box,
	Sphere,
	Capsule
};

UENUM(BlueprintType)
enum class EMeshType : uint8
{
	None,
	StaticMesh,
	SkeletalMesh
};