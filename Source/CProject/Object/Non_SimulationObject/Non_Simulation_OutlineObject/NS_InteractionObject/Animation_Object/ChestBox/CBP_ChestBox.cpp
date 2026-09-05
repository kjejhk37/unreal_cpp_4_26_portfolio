// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/NS_InteractionObject/Animation_Object/ChestBox/CBP_ChestBox.h"
#include "Components/TimelineComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/ShapeComponent.h"

#include "Logger/Logger.h"

#include "Macro/MyMacro.h"
#include "Macro/KismetMacro.h"


ACBP_ChestBox::ACBP_ChestBox()
{
	Set_NonSimul_ComponentsBase(EMeshType::StaticMesh, ECollisionType::Box);
}

void ACBP_ChestBox::BeginPlay()
{
	Super::BeginPlay();

	if (BlendCurveOnAnimation != nullptr)
	{
		FOnTimelineEventStatic TimelineFinishedCallback;
		TimelineFinishedCallback.BindUFunction(this, FName("OpenEnd"));
		AnimationTimeLine->SetTimelineFinishedFunc(TimelineFinishedCallback);
	}

	ActorEndRotator = FRotator();
	StartTransform = FTransform();
	EndTransform = StartTransform;
	EndTransform.SetRotation(FQuat(FRotator(0,0,-120)));

	staticMesh->SetRelativeTransform(StartTransform);

	isOnceInteraction  = false;

}

void ACBP_ChestBox::Interaction(AActor* const InteractionActor, bool& Success, AActor*& ResultActor)
{
	Super::Interaction(InteractionActor, Success, ResultActor);

	if (Success == true)
	{
		interactionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		LockParticle->bHiddenInGame = true;
	}


}

void ACBP_ChestBox::OpenEnd()
{
	for (TSubclassOf<AActor> actor : contents)
	{
		AActor* spawnActor;
		FActorSpawnParameters param;

		SpawnActorUseClass(spawnActor, actor, param);
		spawnActor->SetActorLocation(GetActorLocation());
	}

	interactionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	canOpen = false;

	KismetDelay(TEXT("DeleteBox"), this, 5);
}

void ACBP_ChestBox::DeleteBox()
{
	DestroyActor(this);
}

