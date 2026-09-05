// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Spawn_Skill/Simple/Raven/CBP_Raven_Spawn.h"
#include "Particles/ParticleSystemComponent.h"
#include "Character/CBP_Character.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

#include "Macro/MyMacro.h"
#include "Macro/KismetMacro.h"

#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"

#include "Logger/Logger.h"

ACBP_Raven_Spawn::ACBP_Raven_Spawn()
{
//	SetMesh(EMeshType::SkeletalMesh);
//
//	CreateDefaultSubobjectAuto(particle);
//	particle->SetupAttachment(GetRootComponent());
//	particle->SetRelativeScale3D(FVector(6, 6, 6));
//
//	CreateDefaultSubobjectAuto(AttackComponent);
//	AttackComponent->SetupAttachment(GetRootComponent());
//
//	skeletalMesh->SetRelativeLocation(FVector(0, 0, 300));
//	skeletalMesh->SetRelativeRotation(FRotator(0, -90, 0));
//	skeletalMesh->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));
//
//	AttackComponent->SetSphereRadius(500);
//	AttackComponent->SetCollisionProfileName(FName("Attack"));
}


void ACBP_Raven_Spawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ACBP_Raven_Spawn::BeginPlay()
{
	Super::BeginPlay();

	AttackComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentBeginOverlap);
	AttackComponent->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnComponentEndOverlap);

	if (Timer == FTimerHandle())
	{
		GetWorld()->GetTimerManager().SetTimer
		(
			Timer, this, &ThisClass::Attack, attackCoolTime, true, 0
		);

		SetPauseTimer(Timer);
	}

}

void ACBP_Raven_Spawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACBP_Raven_Spawn::Play(bool const InSuccess, bool& Success)
{
	Super::Play(InSuccess, Success);

	KismetDelay(TEXT("StartAttack"), this, playDelayTime);
}

void ACBP_Raven_Spawn::Attack()
{
	ACBP_Character* instigatorCharacter = Cast<ACBP_Character>(GetInstigator());
	if (instigatorCharacter == nullptr) return;

	for (AActor* actor : AttackActors)
	{
		if (ACBP_Character* character = Cast<ACBP_Character>(actor))
		{
//			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), attackParticle, character->GetActorLocation(), 
//				FRotator(0, 0, 0), FVector(1, 1, 1), true);
			bool hostile = false;
			instigatorCharacter->IsHostile(character->camp, hostile);
			if (hostile == false) continue;
			
			ACBP_Skill* skill;

			instigatorCharacter->SkillSpawn(AttackskillClass, skill);

			if (skill == nullptr) continue;

			FVector skillLocation = character->GetActorLocation();
			skillLocation.Z += 10 - character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();


			skill->SetActorLocation(skillLocation);
			skill->damage = ThisClass::damage;

			bool InSuccess = true;
			bool OutSuccess = false;
			skill->Play(InSuccess, OutSuccess);
		}
	}

	attackCount--;

	if (attackCount <= 0)
	{
		SetPauseTimer(Timer);

		particle->Deactivate();

		KismetDelay(TEXT("EndSkill"), this, endPlayDelayTime);
	}

}

void ACBP_Raven_Spawn::StartAttack()
{
	SetUnPauseTimer(Timer);
}

void ACBP_Raven_Spawn::EndSkill()
{
	DestroyActor(this);
}

void ACBP_Raven_Spawn::SetMesh(EMeshType newMeshType)
{
	Super::SetMesh(newMeshType);
}

void ACBP_Raven_Spawn::SetSpawn(AActor* centerActor)
{
	Super::SetSpawn(centerActor);

	FVector start = GetActorLocation();

	switch (meshType)
	{
	case EMeshType::StaticMesh:
		start = staticMesh->GetComponentLocation();
		break;
	case EMeshType::SkeletalMesh:
		start = skeletalMesh->GetComponentLocation();
		break;

	}

	FHitResult result;

	UKismetSystemLibrary::LineTraceSingle(
		GetWorld(),
		start,
		GetActorLocation() + FVector(0,0,-500),
		ETraceTypeQuery::TraceTypeQuery7,
		false,
		{},
		EDrawDebugTrace::Type::None,
		result,
		true
	);

	if (result.bBlockingHit == true)
	{
		particle->SetWorldLocation(result.Location + FVector(0,0,1));

		FRotator Rotator;
		float const Roll = +UKismetMathLibrary::DegAtan2(result.Normal.Y, result.Normal.Z);
		float const Pitch = -UKismetMathLibrary::DegAtan2(result.Normal.X, result.Normal.Z);

		Rotator = { Pitch, 0, Roll };

		particle->SetWorldRotation(Rotator);

	}


}

void ACBP_Raven_Spawn::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AttackActors.Add(OtherActor);
}

void ACBP_Raven_Spawn::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AttackActors.Remove(OtherActor);
}