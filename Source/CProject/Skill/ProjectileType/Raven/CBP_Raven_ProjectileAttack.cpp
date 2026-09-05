// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/ProjectileType/Raven/CBP_Raven_ProjectileAttack.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Character/CBP_Character.h"
#include "Character/Player/CBP_Player.h"

#include "Kismet/GameplayStatics.h"

#include "Particle/CBP_Particle.h"

#include "Macro/MyMacro.h"
#include "Macro/MathMacro.h"
#include "Macro/KismetMacro.h"

#include "Logger/Logger.h"


ACBP_Raven_ProjectileAttack::ACBP_Raven_ProjectileAttack()
{
	CreateDefaultSubobjectAuto(RavenMesh);
	CreateDefaultSubobjectAuto(AttackCollision);

	RavenMesh->SetupAttachment(GetRootComponent());
	AttackCollision->SetupAttachment(GetRootComponent());

	AttackCollision->SetCollisionProfileName("Attack");

	Particle->SetupAttachment(RavenMesh);

	RavenMesh->SetRelativeRotation(RotatorXYZ(0, 0, -90));
	center->SetWorldScale3D(FVector(4, 4, 4));

	attackPushType = EAttackPushType::WeaponLocation;
}

void ACBP_Raven_ProjectileAttack::BeginPlay()
{
	Super::BeginPlay();

	AttackCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentBeginOverlap);
}

void ACBP_Raven_ProjectileAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACBP_Raven_ProjectileAttack::Play(bool const InSuccess, bool & Success)
{
	Super::Play(InSuccess, Success);

	if (ACBP_Player* player = Cast<ACBP_Player>(GetInstigator()))
	{
		APlayerCameraManager* playerManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
		if (playerManager != nullptr)
		{
			FVector cameraLocation = playerManager->GetCameraLocation();
			float lenght = (endPosition - startPosition).Size();
			FVector cameraForward = playerManager->GetCameraRotation().Quaternion().GetForwardVector();

			endPosition = cameraLocation + cameraForward * lenght;
		}
	}

	KismetDelay(TEXT("ClearArray"), this, 0.5f);
}

void ACBP_Raven_ProjectileAttack::ClearArray()
{
	AttackedActor.Empty();
	AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	KismetDelay(TEXT("ClearArray"), this, 0.5f);
	AttackCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACBP_Raven_ProjectileAttack::SetStart()
{
	Particle->Activate(true);
	AttackedActor.Empty();
}

void ACBP_Raven_ProjectileAttack::SetEnd()
{
	Super::SetEnd();
	Particle->Deactivate();
}

void ACBP_Raven_ProjectileAttack::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
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