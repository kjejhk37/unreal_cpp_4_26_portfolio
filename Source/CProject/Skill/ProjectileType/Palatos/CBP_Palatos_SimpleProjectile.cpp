// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/ProjectileType/Palatos/CBP_Palatos_SimpleProjectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Character/CBP_Character.h"
#include "Character/Player/CBP_Player.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Kismet/GameplayStatics.h"

#include "Particle/CBP_Particle.h"

#include "Macro/MyMacro.h"
#include "Macro/MathMacro.h"
#include "Macro/KismetMacro.h"

#include "Logger/Logger.h"


ACBP_Palatos_SimpleProjectile::ACBP_Palatos_SimpleProjectile()
{
	CreateDefaultSubobjectAuto(PalatosMesh);
	CreateDefaultSubobjectAuto(ShieldMesh);
	CreateDefaultSubobjectAuto(SworldMesh);
	CreateDefaultSubobjectAuto(AttackCollision);

	PalatosMesh->SetupAttachment(GetRootComponent());
	PalatosMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AttackCollision->SetupAttachment(GetRootComponent());
	AttackCollision->SetCollisionProfileName("Attack");
	AttackCollision->SetSphereRadius(100);
	AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Particle->SetupAttachment(PalatosMesh);

	PalatosMesh->SetRelativeRotation(RotatorXYZ(0, 0, -90));
	PalatosMesh->SetRelativeLocation(FVector(0, 0, -90));
	center->SetWorldScale3D(FVector(1, 1, 1));

	attackPushType = EAttackPushType::PushVector;
}

void ACBP_Palatos_SimpleProjectile::BeginPlay()
{
	Super::BeginPlay();

	SetAttachRules(Rule);
	ShieldMesh->AttachToComponent(PalatosMesh, Rule, shieldSocketName);
	SworldMesh->AttachToComponent(PalatosMesh, Rule, swordSocketName);

	AttackCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentBeginOverlap);
}

void ACBP_Palatos_SimpleProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACBP_Palatos_SimpleProjectile::Play(bool const InSuccess, bool & Success)
{
//	Super::Play(InSuccess, Success);

	SpawnMeshes();
	isPlay = true;
	isDelay = true;
	curPlayTime = 0.0f;
	Projectile->Velocity = FVector(0, 0, 0);
	Particle->SetVisibility(true);

	Success = true;

	AttackCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

//	KismetDelay(TEXT("ClearArray"), this, 0.5f);
}

void ACBP_Palatos_SimpleProjectile::ClearArray()
{
//	AttackedActor.Empty();
//	AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
//
//	KismetDelay(TEXT("ClearArray"), this, 0.5f);
//	AttackCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACBP_Palatos_SimpleProjectile::SetStart()
{
	Particle->Activate(true);
	AttackedActor.Empty();
}

void ACBP_Palatos_SimpleProjectile::SetEnd()
{
	Super::SetEnd();
	Particle->Deactivate();
}

void ACBP_Palatos_SimpleProjectile::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (AttackedActor.Contains(OtherActor) == true)
		return;

	AttackedActor.Add(OtherActor);

	ACBP_Character* character = Cast<ACBP_Character>(OtherActor);
	if (character == nullptr) return;

	FHitResult result;

	UKismetSystemLibrary::LineTraceSingle(
		GetWorld(),
		GetActorLocation(),
		character->GetActorLocation(),
		ETraceTypeQuery::TraceTypeQuery6,
		false,
		{ GetInstigator() },
		EDrawDebugTrace::Type::None,
		result,
		true
	);

	FVector particleLocation = GetActorLocation();

	if (result.bBlockingHit == true)
	{
		particleLocation = result.Location;
	}

	ECharacterDamagedType damageType = ECharacterDamagedType::Failling;
	F_Hp_Update_Value resultDamage;
	character->AddDamage(this, damageType, resultDamage);

	if (damageType == ECharacterDamagedType::Failling) return;

	FTransform transform;
	transform.SetLocation(particleLocation);

	if (attackParticle != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), attackParticle, particleLocation,
			FRotator(0, 0, 0), FVector(1, 1, 1), true);
	}

	if (attackParticleActorClass != nullptr)
	{
		ACBP_Particle* particleActor;
		FActorSpawnParameters param;

		SpawnActorUseClass(particleActor, attackParticleActorClass, param);
		particleActor->SetActorLocation(particleLocation);

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

void ACBP_Palatos_SimpleProjectile::SetSpawn(AActor* centerActor)
{
	Projectile->InitialSpeed = moveSpeed;
	Projectile->MaxSpeed = moveSpeed;

	bool succees;
	ThisClass::SetPointersToWorldPos(centerActor,succees);

	SetActorLocation(startPosition);

	FRotator rotator = UKismetMathLibrary::FindLookAtRotation(startPosition, endPosition);
	SetActorRotation(rotator);

}
