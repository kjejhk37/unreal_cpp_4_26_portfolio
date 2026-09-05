// Fill out your copyright notice in the Description page of Project Settings.


#include "Particle/CBP_Particle.h"
#include "Particles/ParticleSystemComponent.h"
#include "Macro/KismetMacro.h"
#include "Macro/MyMacro.h"

// Sets default values
ACBP_Particle::ACBP_Particle()
{
//	PrimaryActorTick.bCanEverTick = true;

	CreateDefaultSubobjectAuto(center);
	SetRootComponent(center);
	CreateDefaultSubobjectAuto(particle);
	particle->SetupAttachment(center);
}

void ACBP_Particle::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACBP_Particle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACBP_Particle::Play()
{
	KismetDelay(TEXT("start"), this, StartDelayTime);
}

void ACBP_Particle::start()
{
	particle->Activate();
	KismetDelay(TEXT("end"), this, PlayTime);
}

void ACBP_Particle::end()
{
	particle->Deactivate();
	KismetDelay(TEXT("StartNextParticle"), this, EndDelayTime);
}

void ACBP_Particle::StartNextParticle()
{
	if (nextParticles.IsValidIndex(0))
	{
		ACBP_Particle* nextParticle;
		FActorSpawnParameters param;

		SpawnActorUseClass(nextParticle, nextParticles[0].particleClass, param);
		nextParticle->SetParticlesBase(nextParticles);
		nextParticle->Play();
	}

	DestroyActor(this);
}

void ACBP_Particle::SetParticlesBase(TArray<F_ParticleActorData> data)
{
	nextParticles = data;

	if (nextParticles.IsValidIndex(0))
	{
		StartDelayTime = nextParticles[0].StartDelayTime;
		EndDelayTime = nextParticles[0].EndDelayTime;

		nextParticles.RemoveAt(0);
	}
}