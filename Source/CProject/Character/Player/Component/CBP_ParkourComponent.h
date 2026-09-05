// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
// UCBP_ParkourComponent



#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"

#include "CBP_ParkourComponent.generated.h"


UENUM(BlueprintType)
enum class EParkourType : uint8
{
	None,
	Climb,
	Fall,
	Slide,
	Normal,
	Short,
	Wall,
	Max
};

// uint8 => 형식의 타입 , 주소값의 크기?

UENUM(BlueprintType)
enum class EArrowType : uint8
{
	Center,
	Ceil,
	Floor,
	Left,
	Right,
	Land,
	Max
};

// DataTable의 일부를 상속받아야 DataTable로 사용가능
USTRUCT(BlueprintType)
struct FParkourData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere) EParkourType Type;

	UPROPERTY(EditAnyWhere) class UAnimMontage* Montage;
	UPROPERTY(EditAnyWhere) float PlayRate = 1.0f;
	UPROPERTY(EditAnyWhere) FName Section;
	UPROPERTY(EditAnyWhere) float MinDis;
	UPROPERTY(EditAnyWhere) float MaxDis;
	UPROPERTY(EditAnyWhere) float Extent;

};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CPROJECT_API UCBP_ParkourComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCBP_ParkourComponent();

protected:
	virtual void BeginPlay() override;

public:
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void BeginParkour();
	void BeginLandedParkour();


	UFUNCTION()
		void EndParkour(UAnimMontage* const Montage, bool bInterrupted);

	UPROPERTY(BlueprintReadOnly) EParkourType ParkourType = EParkourType::None;

private:
	void TraceArrow(EArrowType const Type);
	void TraceCenter();

	void TraceLand();

	bool CheckObstacle();

	bool CheckClimb();
	void BeginClimb();
	void EndClimb();


	bool CheckFall();
	bool CheckDownFall();
	void BeginFall();
	void EndFall();

	bool CheckSlide();
	void BeginSlide();
	void EndSlide();

	bool CheckOthers(EParkourType const Type, FParkourData& Data);
	void BeginOthers(EParkourType const Type, FParkourData const& Data);
	void EndOthers();


private:
	UPROPERTY(EditDefaultsOnly)
		class UDataTable* DataTable;

	TMap<EParkourType, TArray<FParkourData>> DataMap;

	class UArrowComponent* Arrows[int32(EArrowType::Max)];

	FHitResult Results[int32(EArrowType::Max)];

	float TraceDistance = 500;
	float AcceptableAngle = 30;

	AActor* HitObstacle;
	FVector HitObstacleExtent;
	bool Obstacle_Is_ParKourTerrain = false;

	float HitDistance;
	float Yaw;

	bool bFalling = false;

	class AActor* Target;

	float FallingTime = 0;	//이건 작동되는지 확인후 바꿀것 (떨어지는 시간에 따라서구르도록 할 것)
};

