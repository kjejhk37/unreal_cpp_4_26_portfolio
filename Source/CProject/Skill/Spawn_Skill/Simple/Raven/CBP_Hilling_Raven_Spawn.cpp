// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Spawn_Skill/Simple/Raven/CBP_Hilling_Raven_Spawn.h"

#include "Particles/ParticleSystemComponent.h"
#include "Character/CBP_Character.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

#include "Macro/MyMacro.h"
#include "Macro/KismetMacro.h"

#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"

#include "Logger/Logger.h"

ACBP_Hilling_Raven_Spawn::ACBP_Hilling_Raven_Spawn()
{
	SetMesh(EMeshType::StaticMesh);

	CreateDefaultSubobjectAuto(particle);
	particle->SetupAttachment(GetRootComponent());
	particle->SetRelativeScale3D(FVector(6, 6, 6));

	CreateDefaultSubobjectAuto(AttackComponent);
	AttackComponent->SetupAttachment(GetRootComponent());

	staticMesh->SetRelativeLocation(FVector(0, 0, 300));
	staticMesh->SetRelativeScale3D(FVector(3, 3, 3));

	AttackComponent->SetSphereRadius(800);
	AttackComponent->SetCollisionProfileName(FName("Attack"));
}

void ACBP_Hilling_Raven_Spawn::Attack()
{
	ACBP_Character* instigatorCharacter = Cast<ACBP_Character>(GetInstigator());
	if (instigatorCharacter == nullptr) return;

	for (AActor* actor : AttackActors)
	{
		if (ACBP_Character* character = Cast<ACBP_Character>(actor))
		{
			if (character->camp == instigatorCharacter->camp)
			{
				F_Hp_Update_Value resultDamage = damage;

				float damageValue = resultDamage.updateValue;
				float correctValue = rand() % 10 - 5; // -5퍼에서 5퍼
				damageValue += damageValue * (correctValue / 100.0f);
				resultDamage.updateValue = damageValue;

				character->AddHpUpdate(resultDamage);

				SpawnAttackParticle(attackParticle, attackParticleActorClass, character->GetActorLocation());

				FVector fontColor = FVector(0, 1, 0);
				float fontSize = 24;

				if (character->characterName == ECharacterName::Player)
					fontSize = 30;

				SpawnTextActor(
					FString::FromInt(fabsf(resultDamage.updateValue * resultDamage.updateCount)),
					character->GetActorLocation(),
					fontColor,
					fontSize);

			}

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