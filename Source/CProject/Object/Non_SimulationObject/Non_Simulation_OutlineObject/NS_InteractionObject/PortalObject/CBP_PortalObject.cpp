// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/NS_InteractionObject/PortalObject/CBP_PortalObject.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"

#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ShapeComponent.h"

#include "Kismet/GameplayStatics.h"

#include "Macro/MyMacro.h"


ACBP_PortalObject::ACBP_PortalObject()
{
	Set_NonSimul_ComponentsBase(EMeshType::None, ECollisionType::Sphere);
}

void ACBP_PortalObject::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}

void ACBP_PortalObject::BeginPlay()
{
	Super::BeginPlay();

}

void ACBP_PortalObject::Interaction(AActor* const InteractionActor, bool& Success, AActor*& ResultActor)
{
	if (isLock == true) return;

	Super::Interaction(InteractionActor, Success, ResultActor);

	switch (portalType)
	{
	case EPortalType::None:
		break;
	case EPortalType::NextPos:
		InteractionActor->SetActorLocation(nextPos);
		break;
	case EPortalType::NextPortal:
		if (nextPortalObject != nullptr)
			InteractionActor->SetActorLocation(nextPortalObject->GetActorLocation());
		break;
	case EPortalType::NextLevel:
		UGameplayStatics::OpenLevel(this, nextLevel);
		return;
		break;
	}

	Success = true;
	ResultActor = nullptr;
	InteractionParticle->Activate(true);

	if (portalParticle != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), portalParticle, InteractionActor->GetActorLocation(),
			FRotator(0, 0, 0), FVector(1, 1, 1), true);
	}
}

void ACBP_PortalObject::SetLock(bool inLock)
{
	Super::SetLock(inLock);

}

void ACBP_PortalObject::Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType)
{
	Super::Set_NonSimul_ComponentsBase(newMeshType, newInteractionType);

	CreateDefaultSubobjectAuto(particle);
	particle->SetupAttachment(GetRootComponent());

}

void ACBP_PortalObject::SetBeginPlay()
{

}