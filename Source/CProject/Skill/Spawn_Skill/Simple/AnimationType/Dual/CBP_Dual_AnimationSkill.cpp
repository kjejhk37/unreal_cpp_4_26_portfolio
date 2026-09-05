// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Spawn_Skill/Simple/AnimationType/Dual/CBP_Dual_AnimationSkill.h"
#include "Components/ShapeComponent.h"
#include "Components/CapsuleComponent.h"

#include "Character/CBP_Character.h"

#include "Kismet/GameplayStatics.h"

#include "Macro/MyMacro.h"
#include "Macro/MathMacro.h"
#include "Macro/KismetMacro.h"

#include "Logger/Logger.h"


ACBP_Dual_AnimationSkill::ACBP_Dual_AnimationSkill()
{
	attackCollisionType = ECollisionType::Capsule;
	SetMesh(EMeshType::StaticMesh);

	Cast<UCapsuleComponent>(attackCollsiion)->SetCapsuleHalfHeight(90);
	Cast<UCapsuleComponent>(attackCollsiion)->SetCapsuleRadius(10);

	attackCollsiion->SetRelativeLocation(FVector(0, 0, 70));

}
void ACBP_Dual_AnimationSkill::BeginPlay()
{
	Super::BeginPlay();

}


void ACBP_Dual_AnimationSkill::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OverlapedActors.Contains(OtherActor) == true)
		return;

	OverlapedActors.Add(OtherActor);

	ACBP_Character* character = Cast<ACBP_Character>(OtherActor);
	if (character == nullptr) return;

	ECharacterDamagedType damageType = ECharacterDamagedType::Failling;
	F_Hp_Update_Value resultDamage;
	character->AddDamage(this, damageType, resultDamage);

	if (damageType == ECharacterDamagedType::Failling) return;

	FVector ParticleLocation = OtherActor->GetActorLocation();

	TArray<FHitResult> results;

	UKismetSystemLibrary::SphereTraceMultiForObjects(
		GetWorld(),
		staticMesh->GetSocketLocation(FName("SerchStart")),
		staticMesh->GetSocketLocation(FName("Trail_End")),
		10,
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

