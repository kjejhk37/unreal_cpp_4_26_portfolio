// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/Component/CBP_ParkourComponent.h"

#include "Object/Non_SimulationObject/CBP_TerrainObject.h"

#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Character/Player/CBP_Player.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Logger/Logger.h"

#define Arrow_32Type(x) int32(EArrowType::x)
#define RArrow_32Type(x) Results[int32(EArrowType::x)]

UCBP_ParkourComponent::UCBP_ParkourComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	for (int32 i = 0; i < int32(EArrowType::Max); ++i)
	{
		Arrows[i] = CreateDefaultSubobject<UArrowComponent>(FName("Arrow" + FString::FromInt(i)));
	}

	// Arrows[int32(EArrowType::Center)]; => 만든자리가 Center라 생략
	Arrows[int32(EArrowType::Ceil)]->SetRelativeLocation(FVector(0, 0, 80));
	Arrows[int32(EArrowType::Floor)]->SetRelativeLocation(FVector(0, 0, -80));
	Arrows[int32(EArrowType::Left)]->SetRelativeLocation(FVector(0, 30, 0));
	Arrows[int32(EArrowType::Right)]->SetRelativeLocation(FVector(0, -30, 0));
	Arrows[int32(EArrowType::Land)]->SetRelativeLocation(FVector(200, 0, 100));
	Arrows[int32(EArrowType::Land)]->SetRelativeRotation(FRotator(-90, 0, 0));
}

void UCBP_ParkourComponent::BeginPlay()
{
	Super::BeginPlay();
	
//	Cast<ACharacter>(GetOwner())->GetMesh()->GetAnimInstance()->OnMontageBlendingOut.AddDynamic(this, &ThisClass::EndParkour);

	for (int32 i = 0; i < int32(EArrowType::Max); ++i)
	{
		FAttachmentTransformRules const Rules(EAttachmentRule::KeepRelative, true);
		Arrows[i]->AttachToComponent(GetOwner()->GetRootComponent(), Rules);
	}

	if (DataTable != nullptr)
	{
		TArray<FParkourData const*> Rows;

		DataTable->GetAllRows("", Rows);

		for (int32 key = int32(EParkourType::Climb); key < int32(EParkourType::Max); ++key)
		{
			TArray<FParkourData> Value;
			for (auto& Row : Rows)
				if (Row->Type == EParkourType(key))
					Value.Add(*Row);

			DataMap.Add(EParkourType(key), Value);
		}
	}
}


void UCBP_ParkourComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TraceCenter();

	if (HitObstacle != nullptr)
	{
		TraceArrow(EArrowType::Ceil);
		TraceArrow(EArrowType::Floor);
		TraceArrow(EArrowType::Left);
		TraceArrow(EArrowType::Right);
	}

	TraceLand();
}


void UCBP_ParkourComponent::BeginParkour()
{
	if (ParkourType != EParkourType::None)
		return;

	if (CheckObstacle() == true)
	{
		if (CheckDownFall() == true && bFalling == false)
		{
			BeginFall();
		}
		else if (CheckClimb() == true)
		{
			BeginClimb();
		}
		else if (CheckSlide() == true && bFalling == false)
		{
			BeginSlide();
		}
		else {
			if (Results[int32(EArrowType::Ceil)].bBlockingHit == false && bFalling == false)
			{
				float const Dot = FVector::DotProduct(
					Results[int32(EArrowType::Center)].Normal,
					HitObstacle->GetActorForwardVector()
				);

				if (FMath::IsNearlyZero(Dot, 0.1f) == true)
				{
					for (int32 i = int32(EParkourType::Normal); i < int32(EParkourType::Max); ++i)
					{
						FParkourData Data;
						if (CheckOthers(EParkourType(i), Data) == true) {
							BeginOthers(EParkourType(i), Data);
							break;
						}
					}
				}
			}
		}
	}

}

void UCBP_ParkourComponent::BeginLandedParkour()
{
	if (CheckFall() == true && bFalling)
	{
		BeginFall();
	}
}

void UCBP_ParkourComponent::EndParkour(UAnimMontage* const Montage, bool bInterrupted)
{
	switch (ParkourType)
	{
	case EParkourType::Normal:
	case EParkourType::Short:
	case EParkourType::Wall:	EndOthers();	break;
	case EParkourType::Climb:	EndClimb();		break;
	case EParkourType::Fall:	EndFall();		break;
	case EParkourType::Slide:	EndSlide();		break;
	}

	ParkourType = EParkourType::None;

//	Cast<ACBP_Player>(GetOwner())->bUseControllerRotationYaw = true;
}

void UCBP_ParkourComponent::TraceArrow(EArrowType const Type)
{
	UArrowComponent* const Arrow = Arrows[int32(Type)];
	FTransform const Transform = Arrow->GetComponentToWorld();
	FVector const Start = Transform.GetLocation();
	FVector const End = Start + GetOwner()->GetActorForwardVector() * TraceDistance;

	UKismetSystemLibrary::LineTraceSingle
	(
		GetWorld(),
		Start,
		End,
		ETraceTypeQuery::TraceTypeQuery7,
		false,
		{ GetOwner() },
		EDrawDebugTrace::Type::None,
		Results[int32(Type)],
		true
	);
}

void UCBP_ParkourComponent::TraceCenter()
{
	HitObstacle = nullptr;
	HitObstacleExtent = FVector::ZeroVector;
	HitDistance = 0;
	Yaw = 0;

	TraceArrow(EArrowType::Center);

	FHitResult const& Result = Results[int32(EArrowType::Center)];

	if (Result.bBlockingHit == true && Result.GetActor() != nullptr)
	{
		Obstacle_Is_ParKourTerrain = false;

		if (ACBP_TerrainObject* terrainObject = Cast<ACBP_TerrainObject>(Result.Actor))
		{
			Obstacle_Is_ParKourTerrain = true;
			HitObstacle = Result.GetActor();

			FVector Min, Max;

			HitObstacleExtent = terrainObject->TerrainCollision->GetScaledBoxExtent() * 2;

			ACharacter* Owner = Cast<ACharacter>(GetOwner());
			HitObstacleExtent.Z = HitObstacleExtent.Z + Result.Actor->GetActorLocation().Z
				- Owner->GetActorLocation().Z - Owner->GetMesh()->GetRelativeLocation().Z;

			HitDistance = Result.Distance;
			Yaw = UKismetMathLibrary::MakeRotFromX(-Result.Normal).Yaw;
		}
		
//		typedef UStaticMeshComponent MeshType;
//
//		if (MeshType const* const Mesh = Cast<MeshType>(Result.Actor->GetComponentByClass(MeshType::StaticClass())))
//		{
//			HitObstacle = Result.GetActor();
//
//			FVector Min, Max;
//
//			// Mesh의 경계 Cube형태로 받아옴
//			Mesh->GetLocalBounds(Min, Max);
//
//			ACharacter* Owner = Cast<ACharacter>(GetOwner());
//
//			HitObstacleExtent = FVector(Max.X - Min.X, Max.Y - Min.Y, Max.Z - Min.Z) * HitObstacle->GetActorScale3D();
//
//			HitObstacleExtent.Z = HitObstacleExtent.Z + Result.Actor->GetActorLocation().Z
//				- Owner->GetActorLocation().Z - Owner->GetMesh()->GetRelativeLocation().Z;
//
//			HitDistance = Result.Distance;
//			Yaw = UKismetMathLibrary::MakeRotFromX(-Result.Normal).Yaw;
//		}
	}
}

void UCBP_ParkourComponent::TraceLand()
{
	if (Cast<ACharacter>(GetOwner())->GetCharacterMovement()->IsFalling() == true && bFalling == false)
	{
		bFalling = true;

		FVector const Start = Arrows[Arrow_32Type(Land)]->GetComponentToWorld().GetLocation();
		FVector const End =
			Start +
			Arrows[Arrow_32Type(Land)]->GetComponentToWorld().GetRotation().GetForwardVector()*
			DataMap[EParkourType::Fall][0].Extent;

		UKismetSystemLibrary::LineTraceSingle
		(
			GetWorld(),
			Start,
			End,
			ETraceTypeQuery::TraceTypeQuery7,
			false,
			{ GetOwner() },
			EDrawDebugTrace::Type::None,
			RArrow_32Type(Land),
			true
		);
	}

	if (bFalling == true && Cast<ACharacter>(GetOwner())->GetCharacterMovement()->IsFalling() == false)
	{
		bFalling = false;
	}
}

bool UCBP_ParkourComponent::CheckObstacle()
{
	if (Obstacle_Is_ParKourTerrain == false) return false;
	
	bool bResult = true;

	// x &= y => x에 x & y를 대입

	bResult &= RArrow_32Type(Center).bBlockingHit;
	bResult &= RArrow_32Type(Left).bBlockingHit;
	bResult &= RArrow_32Type(Right).bBlockingHit;

	if (bResult == true)
	{
		FVector const Center = RArrow_32Type(Center).Normal;
		FVector const Left = RArrow_32Type(Left).Normal;
		FVector const Right = RArrow_32Type(Right).Normal;

		if (Center.Equals(Left) == false || Center.Equals(Right) == false)
			return false;


		//#define Class true

#ifdef Class
		FVector const Start = RArrow_32Type(Center).Location;
		FVector const End = GetOwner()->GetActorLocation();

		float const LookAtYaw = UKismetMathLibrary::FindLookAtRotation(Start, End).Yaw;
		float const NormalYaw = UKismetMathLibrary::MakeRotFromX(Center).Yaw;

		Logger::Print(abs(abs(LookAtYaw) - abs(NormalYaw)));

		if (abs(abs(LookAtYaw) - abs(NormalYaw)) <= AcceptableAngle)
			return true;
#else
		float const Angle = abs(GetOwner()->GetActorRotation().Yaw - Yaw);
		if (FMath::Min(Angle, 360 - Angle) <= AcceptableAngle)
			return true;
#endif

	}

	return false;
}

bool UCBP_ParkourComponent::CheckClimb()
{

	if (RArrow_32Type(Ceil).bBlockingHit == true)
	{
		TArray<FParkourData> const& Data = DataMap[EParkourType::Climb];

		if (Data[0].MinDis <= HitDistance && HitDistance <= Data[0].MaxDis)
			if (FMath::IsNearlyEqual(Data[0].Extent, HitObstacleExtent.Z, 10) == true)
				return true;
	}

	return false;
}

void UCBP_ParkourComponent::BeginClimb()
{
	ParkourType = EParkourType::Climb;

	ACharacter* const Owner = Cast<ACharacter>(GetOwner());

	Owner->SetActorLocation(RArrow_32Type(Center).Location);
	Owner->SetActorRotation(FRotator(0, Yaw, 0));

	TArray<FParkourData> const& Data = DataMap[EParkourType::Climb];

	Owner->PlayAnimMontage(Data[0].Montage, Data[0].PlayRate, Data[0].Section);
	Owner->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);

}

void UCBP_ParkourComponent::EndClimb()
{
	Cast<ACharacter>(GetOwner())->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	GetOwner()->AddActorLocalOffset(FVector(0, 0, 30), true);
}


bool UCBP_ParkourComponent::CheckFall()
{
	if (bFalling != true)
		return false;

	FHitResult result;

	UKismetSystemLibrary::LineTraceSingle(
		GetWorld(),
		GetOwner()->GetActorLocation(),
		GetOwner()->GetActorLocation() + FVector(0, 0, -150),
		ETraceTypeQuery::TraceTypeQuery7,
		false,
		{ GetOwner() },
		EDrawDebugTrace::Type::None,
		result,
		true
	);

	if (result.bBlockingHit == false)
		return false;

	float const Distance = RArrow_32Type(Land).Distance;

	TArray<FParkourData> const& DataArray = DataMap[EParkourType::Fall];

	bFalling = (DataArray[0].MinDis <= Distance && Distance <= DataArray[0].MaxDis);

	return bFalling;

}

bool UCBP_ParkourComponent::CheckDownFall()
{
	if (ACBP_Character* character = Cast<ACBP_Character>(GetOwner()))
	{
		return character->characterState == ECharacterState::Down;
	}

	return false;
}

void UCBP_ParkourComponent::BeginFall()
{
	ParkourType = EParkourType::Fall;

	TArray<FParkourData> const& DataArray = DataMap[ParkourType];
	Cast<ACharacter>(GetOwner())->PlayAnimMontage(DataArray[0].Montage, DataArray[0].PlayRate, DataArray[0].Section);
}

void UCBP_ParkourComponent::EndFall()
{
	bFalling = false;
}

bool UCBP_ParkourComponent::CheckSlide()
{
	if (RArrow_32Type(Floor).bBlockingHit == false)
	{
		TArray<FParkourData> const& DataArray = DataMap[EParkourType::Slide];

		if (DataArray[0].MinDis <= HitDistance && HitDistance <= DataArray[0].MaxDis)
		{

			FVector const Start = Arrows[int32(EArrowType::Floor)]->GetComponentToWorld().GetLocation() + FVector(0, 0, DataArray[0].Extent);
			FVector const End = Start + GetOwner()->GetActorForwardVector() * TraceDistance;

			bool const Result = UKismetSystemLibrary::BoxTraceSingle
			(
				GetWorld(),
				Start,
				End,
				FVector(0, DataArray[0].Extent, DataArray[0].Extent),
				GetOwner()->GetActorRotation(),
				ETraceTypeQuery::TraceTypeQuery7,
				false,
				{ GetOwner() },
				EDrawDebugTrace::Type::None,
				RArrow_32Type(Floor),
				true
			);


			return !(Result == true || Cast<ACharacter>(GetOwner())->GetCharacterMovement()->Velocity.Size2D() < 450);
		}
	}

	return false;
}

void UCBP_ParkourComponent::BeginSlide()
{
	ParkourType = EParkourType::Slide;

	TArray<FParkourData> const& DataArray = DataMap[ParkourType];

	Cast<ACharacter>(GetOwner())->PlayAnimMontage(DataArray[0].Montage, DataArray[0].PlayRate, DataArray[0].Section);

	Target = HitObstacle;
//	Target->SetActorEnableCollision(false);

	if (ACBP_TerrainObject* terrainObject = Cast<ACBP_TerrainObject>(Target))
	{
		terrainObject->TerrainCollision->SetCollisionProfileName(FName("ParkourTerrain"));
	}
	
}

void UCBP_ParkourComponent::EndSlide()
{
//	Target->SetActorEnableCollision(true);
	if (ACBP_TerrainObject* terrainObject = Cast<ACBP_TerrainObject>(Target))
	{
		terrainObject->TerrainCollision->SetCollisionProfileName(FName("Terrain"));
	}
	Target = nullptr;
}

bool UCBP_ParkourComponent::CheckOthers(EParkourType const Type, FParkourData& Data)
{
	TArray<FParkourData> const& DataArray = DataMap[Type];

	for (int32 i = 0; i < DataArray.Num(); ++i)
	{
		if (FMath::IsNearlyEqual(DataArray[i].Extent, HitObstacleExtent.Y, 10) == true)
		{
			if (DataArray[i].MinDis <= HitDistance && HitDistance <= DataArray[i].MaxDis)
			{
				Data = DataArray[i];
				return true;
			}
			else continue;
		}
	}

	return false;
}

void UCBP_ParkourComponent::BeginOthers(EParkourType const Type, FParkourData const & Data)
{
	ParkourType = Type;

	ACharacter* const Owner = Cast<ACharacter>(GetOwner());

	Owner->SetActorRotation(FRotator(0, Yaw, 0));
	Owner->PlayAnimMontage(Data.Montage, Data.PlayRate, Data.Section);

	Target = HitObstacle;
//	Target->SetActorEnableCollision(false);

	if (ACBP_TerrainObject* terrainObject = Cast<ACBP_TerrainObject>(Target))
	{
		terrainObject->TerrainCollision->SetCollisionProfileName(FName("ParkourTerrain"));
	}

	Owner->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
}

void UCBP_ParkourComponent::EndOthers()
{
	Cast<ACharacter>(GetOwner())->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
//	Target->SetActorEnableCollision(true);
	if (ACBP_TerrainObject* terrainObject = Cast<ACBP_TerrainObject>(Target))
	{
		terrainObject->TerrainCollision->SetCollisionProfileName(FName("Terrain"));
	}
	Target = nullptr;
}
