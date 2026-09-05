// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/Sub_Quest/ArriveQuest/CBP_Arrive_Sub_QuestActor.h"

#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"

#include "Character/Player/CBP_Player.h"

#include "Macro/MyMacro.h"

ACBP_Arrive_Sub_QuestActor::ACBP_Arrive_Sub_QuestActor()
{
	CreateDefaultSubobjectAuto(ArriveCollision);

	CreateDefaultSubobjectAuto(particle);
	particle->SetupAttachment(ArriveCollision);

	ArriveCollision->SetupAttachment(GetRootComponent());
	ArriveCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ArriveCollision->SetCollisionProfileName(FName("Interaction"));
}

void ACBP_Arrive_Sub_QuestActor::BeginPlay()
{
	Super::BeginPlay();

	ArriveCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ArriveCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentBeginOverlap);
}

void ACBP_Arrive_Sub_QuestActor::StartQuest()
{
	Super::StartQuest();

	SetActorLocation(QuestLocation);
	ArriveCollision->SetBoxExtent(CollisionExtent);

	ArriveCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACBP_Arrive_Sub_QuestActor::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (ACBP_Player* player = Cast<ACBP_Player>(OtherActor))
	{
		EndQuest();
	}
}