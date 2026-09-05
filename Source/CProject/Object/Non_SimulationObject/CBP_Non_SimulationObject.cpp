// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Non_SimulationObject/CBP_Non_SimulationObject.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Macro/MyMacro.h"


ACBP_Non_SimulationObject::ACBP_Non_SimulationObject()
{

//	PrimaryActorTick.bCanEverTick = true;
}

void ACBP_Non_SimulationObject::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}

void ACBP_Non_SimulationObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
//void ACBP_Non_SimulationObject::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

void ACBP_Non_SimulationObject::SetVisible(bool newVisible)
{
	switch (meshType)
	{
	case EMeshType::SkeletalMesh:
		skeletalMesh->SetVisibility(newVisible);
		break;
	case EMeshType::StaticMesh:
		staticMesh->SetVisibility(newVisible);
		break;
	}
}

/* ======================== Transform =============================*/
void ACBP_Non_SimulationObject::SetScale(FVector const newScale)
{
	switch (meshType)
	{
	case EMeshType::StaticMesh:
		staticMesh->SetRelativeScale3D(newScale);
		break;
	case EMeshType::SkeletalMesh:
		skeletalMesh->SetRelativeScale3D(newScale);
		break;
	}
}

void ACBP_Non_SimulationObject::SetScaleMesh(FVector const newScale)
{
	switch (meshType)
	{
	case EMeshType::StaticMesh:
		staticMesh->SetRelativeScale3D(newScale);
		break;
	case EMeshType::SkeletalMesh:
		skeletalMesh->SetRelativeScale3D(newScale);
		break;
	}
}

void ACBP_Non_SimulationObject::SetPosition(FVector const newPosition)
{
	switch (meshType)
	{
	case EMeshType::StaticMesh:
		staticMesh->SetRelativeLocation(newPosition);
		break;
	case EMeshType::SkeletalMesh:
		skeletalMesh->SetRelativeLocation(newPosition);
		break;
	}
}

void ACBP_Non_SimulationObject::SetRotation(FRotator const newRotator)
{
	switch (meshType)
	{
	case EMeshType::StaticMesh:
		staticMesh->SetRelativeRotation(newRotator);
		break;
	case EMeshType::SkeletalMesh:
		skeletalMesh->SetRelativeRotation(newRotator);
		break;
	}
}

/*========================== Set Mesh ============================*/
void ACBP_Non_SimulationObject::Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType)
{
	meshType = newMeshType;

	switch (meshType)
	{
	case EMeshType::None:
		break;
	case EMeshType::StaticMesh:
		CreateDefaultSubobjectAuto(staticMesh);
		break;
	case EMeshType::SkeletalMesh:
		CreateDefaultSubobjectAuto(skeletalMesh);
		break;
	}
}
