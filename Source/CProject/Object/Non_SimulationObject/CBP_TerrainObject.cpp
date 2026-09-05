// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Non_SimulationObject/CBP_TerrainObject.h"
#include "Components/BoxComponent.h"

#include "Logger/Logger.h"

ACBP_TerrainObject::ACBP_TerrainObject()
{
	Set_NonSimul_ComponentsBase(EMeshType::StaticMesh, ECollisionType::None);
}

void ACBP_TerrainObject::Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType)
{
	Super::Set_NonSimul_ComponentsBase(newMeshType, newInteractionType);

	TerrainCollision = Cast<UBoxComponent>(CreateDefaultSubobject<UBoxComponent>(TEXT("TerrainCollision")));

	switch (newMeshType)
	{
	case EMeshType::StaticMesh:
		TerrainCollision->SetupAttachment(staticMesh);
		break;
	case EMeshType::SkeletalMesh:
		TerrainCollision->SetupAttachment(skeletalMesh);
		break;
	}

	TerrainCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	TerrainCollision->SetCollisionProfileName(FName("Terrain"));


}

void ACBP_TerrainObject::BeginPlay()
{
	Super::BeginPlay();

//	FVector Min, Max;
//	staticMesh->GetLocalBounds(Min, Max);
//
//	FVector HitObstacleExtent;
//
//	HitObstacleExtent = FVector(Max.X - Min.X, Max.Y - Min.Y, Max.Z - Min.Z) * 0.5f;
//	Logger::Print(HitObstacleExtent,0,60);
//
//	TerrainCollision->SetBoxExtent(HitObstacleExtent);
//	HitObstacleExtent.X = 0;
//	TerrainCollision->SetRelativeLocation(HitObstacleExtent);

}