// Fill out your copyright notice in the Description page of Project Settings.


#include "CBP_TwinSword_MainWeapon.h"

#include "Components/CapsuleComponent.h"
#include "Character/CBP_Character.h"
#include "Kismet/GameplayStatics.h"

#include "Macro/MyMacro.h"
#include "Macro/MathMacro.h"
#include "Macro/KismetMacro.h"


ACBP_TwinSword_MainWeapon::ACBP_TwinSword_MainWeapon()
{
	Set_NonSimul_ComponentsBase(EMeshType::StaticMesh, ECollisionType::None);

	staticMesh->SetCollisionProfileName(FName("NoCollision"));

	Cast<UCapsuleComponent>(attackComponent)->SetCapsuleHalfHeight(60);
	Cast<UCapsuleComponent>(attackComponent)->SetCapsuleRadius(6);

	attackComponent->SetRelativeLocation(FVector(78.5f, 0, 0));
	attackComponent->SetRelativeRotation(RotatorXYZ(0, 90, 0));

	Trail_Start_Socket = FName("Trail_Start");
	Trail_End_Socket = FName("Trail_End");

	main_Weapon_Scale = FVector(1, 1, 1);

	weaponName = EWeaponName::TwinSword;
}

void ACBP_TwinSword_MainWeapon::Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType)
{
	attackCollisionType = ECollisionType::Capsule;
	Super::Set_NonSimul_ComponentsBase(newMeshType, newInteractionType);
}

void ACBP_TwinSword_MainWeapon::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
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

