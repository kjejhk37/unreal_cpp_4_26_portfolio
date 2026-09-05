// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Spawn_Skill/Spawn_Lightning/CBP_LightningSpawnSkill.h"
#include "Particles/ParticleSystemComponent.h"
#include "Character/CBP_Character.h"

#include "Macro/KismetMacro.h"
#include "Macro/MyMacro.h"


ACBP_LightningSpawnSkill::ACBP_LightningSpawnSkill()
{
	CreateDefaultSubobjectAuto(particle);
	particle->SetupAttachment(GetRootComponent());

	CreateDefaultSubobjectAuto(LightingParticle);
	LightingParticle->SetupAttachment(GetRootComponent());

	LightingParticle->bAutoActivate = false;

}

void ACBP_LightningSpawnSkill::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);
}

void ACBP_LightningSpawnSkill::BeginPlay()
{
	Super::BeginPlay();
}

void ACBP_LightningSpawnSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACBP_LightningSpawnSkill::Play(bool const InSuccess, bool & Success)
{
	Super::Play(InSuccess, Success);


	FHitResult result;

	UKismetSystemLibrary::LineTraceSingle(
		GetWorld(),
		GetActorLocation() + FVector(0,0,30),
		GetActorLocation() + FVector(0, 0, -30),
		ETraceTypeQuery::TraceTypeQuery7,
		false,
		{},
		EDrawDebugTrace::Type::None,
		result,
		true
	);

	if (result.bBlockingHit == true)
	{
		SetActorLocation(result.Location + FVector(0, 0, 1));

		FRotator Rotator;
		float const Roll = +UKismetMathLibrary::DegAtan2(result.Normal.Y, result.Normal.Z);
		float const Pitch = -UKismetMathLibrary::DegAtan2(result.Normal.X, result.Normal.Z);

		Rotator = { Pitch, 0, Roll };

		SetActorRotation(Rotator);

	}

	KismetDelay(TEXT("Attack"), this, DelayTime);
}

void ACBP_LightningSpawnSkill::Attack()
{
	SetStart();

	TArray<AActor*> outerActors;

	UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(),
		GetActorLocation(),
		75,
		{ EObjectTypeQuery::ObjectTypeQuery11 },
		nullptr,
		{ GetInstigator() },
		outerActors
	);

	for (AActor* actor : outerActors)
	{
		ACBP_Character* character = Cast<ACBP_Character>(actor);
		if (character == nullptr) continue;

		ECharacterDamagedType damageType = ECharacterDamagedType::Failling;
		F_Hp_Update_Value resultDamage;
		character->AddDamage(this, damageType, resultDamage);

		if (damageType == ECharacterDamagedType::Failling) continue;

		FVector ParticleLocation = character->GetActorLocation();

		ParticleLocation += FVector((rand() % 100 - 50), (rand() % 100 - 50), (rand() % 100 - 50));

		if (attackParticleActorClass != nullptr)
		{
			ACBP_Particle* particleActor;
			FActorSpawnParameters param;

			SpawnActorUseClass(particleActor, attackParticleActorClass, param);
			particleActor->SetActorLocation(ParticleLocation);

			F_ParticleActorData data;
			data.EndDelayTime = 0;
			data.StartDelayTime = 0;

			particleActor->SetParticlesBase({ data });
			particleActor->Play();
		}

		FVector fontColor = FVector(1, 1, 1);
		float fontSize = 24;

		if (character->characterName == ECharacterName::Player)
			fontSize = 30;

		if (damageType == ECharacterDamagedType::Guard)
		{
			fontColor = FVector(1, 1, 0);
			fontSize *= 0.75f;
		}

		SpawnTextActor(
			FString::FromInt(resultDamage.updateValue * resultDamage.updateCount),
			GetActorLocation(),
			fontColor,
			fontSize);

	}

	KismetDelay(TEXT("EndSkill"), this, particlePlayTime);

}

void ACBP_LightningSpawnSkill::SetStart()
{
	LightingParticle->Activate();
	particle->Deactivate();
}

void ACBP_LightningSpawnSkill::EndSkill()
{
	SetEnd();
}

void ACBP_LightningSpawnSkill::SetEnd()
{
	LightingParticle->Deactivate();
	DestroyActor(this);
}

void ACBP_LightningSpawnSkill::SetSpawn(AActor* centerActor)
{
//	Super::SetSpawn();
}

