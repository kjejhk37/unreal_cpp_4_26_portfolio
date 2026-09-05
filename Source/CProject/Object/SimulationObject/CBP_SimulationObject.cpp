// Fill out your copyright notice in the Description page of Project Settings.


#include "CBP_SimulationObject.h"
#include "../../Macro/MyMacro.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ShapeComponent.h"
#include "Components/SkinnedMeshComponent.h"

#include "Logger/Logger.h"

ACBP_SimulationObject::ACBP_SimulationObject()
{
//	PrimaryActorTick.bCanEverTick = true;

}

void ACBP_SimulationObject::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}


void ACBP_SimulationObject::BeginPlay()
{
	Super::BeginPlay();
}

//void ACBP_SimulationObject::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}


/* ==================================== Transform ==========================================*/
void ACBP_SimulationObject::SetScale(FVector const newScale)
{
	if(simulationComponent != NULL)
	{
		simulationComponent->SetRelativeScale3D(newScale);
	}
	else
	{
		switch (meshType)
		{
		case EMeshType::SkeletalMesh:
			skeletalMesh->SetRelativeScale3D(newScale);
			break;
		case EMeshType::StaticMesh:
			staticMesh->SetRelativeScale3D(newScale);
			break;
		}
	}
}

void ACBP_SimulationObject::SetScaleMesh(FVector const newScale)
{
	switch (meshType)
	{
	case EMeshType::SkeletalMesh:
		skeletalMesh->SetRelativeScale3D(newScale);
		break;
	case EMeshType::StaticMesh:
		staticMesh->SetRelativeScale3D(newScale);
		break;
	}
}

void ACBP_SimulationObject::SetPosition(FVector const newPosition)
{
	if (simulationComponent != NULL)
	{
		simulationComponent->SetRelativeLocation(newPosition);
	}
	else
	{
		switch (meshType)
		{
		case EMeshType::SkeletalMesh:
			skeletalMesh->SetRelativeLocation(newPosition);
			break;
		case EMeshType::StaticMesh:
			staticMesh->SetRelativeLocation(newPosition);
			break;
		}
	}
}

void ACBP_SimulationObject::SetRotation(FRotator const newRotator)
{
	if (simulationComponent != NULL)
	{
		simulationComponent->SetRelativeRotation(newRotator);
	}
	else
	{
		switch (meshType)
		{
		case EMeshType::SkeletalMesh:
			skeletalMesh->SetRelativeRotation(newRotator);
			break;
		case EMeshType::StaticMesh:
			staticMesh->SetRelativeRotation(newRotator);
			break;
		}
	}
}

/* ==================================== Set =================================================*/
void ACBP_SimulationObject::SetSimulation(bool newSimul)
{
	if(simulationType != ESimulationType::None)
	{
		simulationComponent->SetSimulatePhysics(newSimul);
	}
	else
	{
		switch (meshType)
		{
		case EMeshType::SkeletalMesh:
			skeletalMesh->SetSimulatePhysics(newSimul);
			break;
		case EMeshType::StaticMesh:
			staticMesh->SetSimulatePhysics(newSimul);
			break;
		}
	}
}

void ACBP_SimulationObject::SetVisible(bool newVisible)
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

void ACBP_SimulationObject::SetImpulse(bool isAtLocation, float power, FVector velocity, FVector Location)
{
	FVector impulse = (velocity * power);

	if (isAtLocation)
	{
		if (simulationType == ESimulationType::None)
		{
			switch (meshType)
			{
			case EMeshType::StaticMesh:
				staticMesh->AddImpulseAtLocation(impulse, Location);
				break;
			case EMeshType::SkeletalMesh:
				skeletalMesh->AddImpulseAtLocation(impulse, Location);
				break;
			}
		}
		else
			simulationComponent->AddImpulseAtLocation(impulse, Location);

	}
	else
	{
		if (simulationType == ESimulationType::None)
		{
			switch (meshType)
			{
			case EMeshType::StaticMesh:
				staticMesh->AddImpulse(impulse,NAME_None,true);
				break;
			case EMeshType::SkeletalMesh:
				skeletalMesh->AddImpulse(impulse, NAME_None, true);
				break;
			}
		}
		else
			simulationComponent->AddImpulse(impulse, NAME_None, true);
	}

}

/* ==================================== Set Compoennt Type =================================*/

void ACBP_SimulationObject::Set_Simul_ComponentsBase(EMeshType newMeshType, ESimulationType newSimulationType, ECollisionType newInteractionType)
{
	meshType = newMeshType;
	simulationType = newSimulationType;

	if (meshType == EMeshType::None && simulationType == ESimulationType::None) {
		return;
	}

	switch (simulationType)
	{
	case ESimulationType::Box:
		simulationComponent = Cast<UShapeComponent>(CreateDefaultSubobject<UBoxComponent>(TEXT("SimulCollision")));
		break;
	case ESimulationType::Sphere:
		simulationComponent = Cast<UShapeComponent>(CreateDefaultSubobject<USphereComponent>(TEXT("SimulCollision")));
		break;
	case ESimulationType::Capsule:
		simulationComponent = Cast<UShapeComponent>(CreateDefaultSubobject<UCapsuleComponent>(TEXT("SimulCollision")));
		break;
	}

	FAttachmentTransformRules const Rules(EAttachmentRule::KeepRelative, true);

	switch (meshType)
	{
	case EMeshType::StaticMesh:
		CreateDefaultSubobjectAuto(staticMesh);
		if (simulationComponent != NULL) {
			staticMesh->AttachToComponent(simulationComponent, Rules);
		}
		break;
	case EMeshType::SkeletalMesh:
		CreateDefaultSubobjectAuto(skeletalMesh);
		if (simulationComponent != NULL) {
			skeletalMesh->AttachToComponent(simulationComponent, Rules);
		}
		break;
	}

	SetSimulation(true);
}