// Fill out your copyright notice in the Description page of Project Settings.


#include "CBP_DualBlade_MainWeapon.h"
#include "Components/CapsuleComponent.h"
#include "Character/CBP_Character.h"
#include "Kismet/GameplayStatics.h"

#include "Macro/MyMacro.h"
#include "Macro/MathMacro.h"
#include "Macro/KismetMacro.h"

#include "Logger/Logger.h"

ACBP_DualBlade_MainWeapon::ACBP_DualBlade_MainWeapon()
{
	Set_NonSimul_ComponentsBase(EMeshType::StaticMesh, ECollisionType::None);

	staticMesh->SetCollisionProfileName(FName("NoCollision"));

	Cast<UCapsuleComponent>(attackComponent)->SetCapsuleHalfHeight(70);
	Cast<UCapsuleComponent>(attackComponent)->SetCapsuleRadius(6);

	attackComponent->SetRelativeLocation(FVector(0, 0, 95));

	Trail_Start_Socket = FName("Trail_Start");
	Trail_End_Socket = FName("Trail_End");

	main_Weapon_Scale = FVector(1, 1, 1);

	weaponName = EWeaponName::DualBlade;
}


void ACBP_DualBlade_MainWeapon::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);
}

void ACBP_DualBlade_MainWeapon::Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType)
{
	attackCollisionType = ECollisionType::Capsule;
	Super::Set_NonSimul_ComponentsBase(newMeshType, newInteractionType);
}

void ACBP_DualBlade_MainWeapon::BeginPlay()
{
	Super::BeginPlay();

}

void ACBP_DualBlade_MainWeapon::Activate(bool InSuccess, bool & OutSuccess)
{
	Super::Activate(InSuccess, OutSuccess);
}

void ACBP_DualBlade_MainWeapon::DeActivate(bool InSuccess, bool & OutSuccess)
{
	Super::DeActivate(InSuccess, OutSuccess);
}

void ACBP_DualBlade_MainWeapon::TrailParticleActivate()
{
	Super::TrailParticleActivate();
}

void ACBP_DualBlade_MainWeapon::TrailParticleDeActivate()
{
	Super::TrailParticleDeActivate();
}

void ACBP_DualBlade_MainWeapon::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OverlapedActors.Contains(OtherActor) == true)
		return;

	OverlapedActors.Add(OtherActor);

	ACBP_Character* character = Cast<ACBP_Character>(OtherActor);
	if (character == nullptr) return;

	ECharacterDamagedType type;
	F_Hp_Update_Value resultDamage;
	
	character->AddDamage(this, type, resultDamage);

	if (type == ECharacterDamagedType::Failling) return;

	FVector ParticleLocation;

	TArray<FHitResult> results;

	UKismetSystemLibrary::SphereTraceMultiForObjects(
		GetWorld(),
		staticMesh->GetSocketLocation(FName("center")),
		staticMesh->GetSocketLocation(FName("Trail_End")),
		6,
		{ EObjectTypeQuery::ObjectTypeQuery11 },
		false,
		{ GetInstigator() },
		EDrawDebugTrace::Type::None,
		results,
		true
	);

	for (FHitResult result : results)
	{
		if (result.Actor == OtherActor)
		{
			ParticleLocation = result.Location;
			break;
		}
	}

	if (attackParticle != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), attackParticle, ParticleLocation,
			FRotator(0, 0, 0), FVector(1, 1, 1), true);
	}

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

	if (type == ECharacterDamagedType::Guard)
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

