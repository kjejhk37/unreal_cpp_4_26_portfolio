// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/ProjectileType/CBP_Projectile_Skill.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Character/CBP_Character.h"
#include "Kismet/GameplayStatics.h"


#include "Macro/MyMacro.h"
#include "Macro/MathMacro.h"
#include "Macro/KismetMacro.h"

#include "Logger/Logger.h"

ACBP_Projectile_Skill::ACBP_Projectile_Skill()
{
	CreateDefaultSubobjectAuto(Particle);
	CreateDefaultSubobjectAuto(Arrow);
	CreateDefaultSubobjectAuto(Projectile);

	FAttachmentTransformRules const Rules(EAttachmentRule::KeepRelative, true);

	Particle->SetupAttachment(center);
	Arrow->SetupAttachment(center);

	Projectile->InitialSpeed = 10000;
	Projectile->MaxSpeed = 10000;
	Projectile->ProjectileGravityScale = 0.0f;
}

void ACBP_Projectile_Skill::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}

void ACBP_Projectile_Skill::BeginPlay()
{
	Super::BeginPlay();
	
	isPlay = false;

}

void ACBP_Projectile_Skill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isPlay == false)
	{
		SetActorLocation(worldStartPosition);
		return;
	}

	curTime += DeltaTime;

	if (isDelay)
	{
		if (curTime >= delayTimes[curSkillIndex]) 
		{
			if (curSkillIndex == 0)
			{
				if (auto* character = Cast<ACBP_Character>(GetInstigator()))
					character->SkillStart();
			}

			isDelay = false;
			curTime = 0;

			ThisClass::SetVelocity(curSkillIndex);

			ThisClass::Attack();

//			Particle->SetVisibility(true);

			if (curSkillIndex != 0)
			{
				if (meshes.IsValidIndex(curSkillIndex - 1) == true)
				{
					DestroyActor(meshes[curSkillIndex - 1]);
				}
			}
		}
	}
	else
	{
		if (curTime >= Times[curSkillIndex])
		{
			if (curSkillIndex == (Times.Num() - 1))
			{
				if (auto* character = Cast<ACBP_Character>(GetInstigator()))
					character->SkillEnd();

				if (meshes.IsValidIndex(curSkillIndex) == true)
				{
					DestroyActor(meshes[curSkillIndex]);
				}

				KismetDelay(TEXT("DestroyThisActor"), this, 5);
			}
			else
			{
				curSkillIndex++;
				curTime = 0;
				isDelay = true;

				Projectile->Velocity = FVector(0, 0, 0);
//				Particle->SetVisibility(true);
			}
		}
	}
	

}

void ACBP_Projectile_Skill::DestroyThisActor()
{
	DestroyActor(this);
}

void ACBP_Projectile_Skill::SetPointersToWorldPos(bool& success)
{
	Times.Empty();
	worldPositions.Empty();

	for (int i = 0; i < localPointers.Num(); i++)
	{
		localPointers[i];
		FVector worldPointer =	(GetActorForwardVector() * localPointers[i].X) +
								(GetActorRightVector() * localPointers[i].Y) +
								(GetActorUpVector() * localPointers[i].Z);

		worldPointer += GetActorLocation();

		worldPositions.Add(worldPointer);

		FVector temp;
		float lenght;

		if (i == 0)
		{
			(GetActorLocation() - worldPointer).ToDirectionAndLength(temp, lenght);

			Times.Add(lenght / Projectile->InitialSpeed);
		}
		else
		{
			(worldPositions[i - 1] - worldPointer).ToDirectionAndLength(temp, lenght);
			Times.Add(lenght / Projectile->InitialSpeed);
		}
	}

	success = (worldPositions.Num() > 0);
}

void ACBP_Projectile_Skill::SpawnMeshes()
{
	for (int i = 0; i < meshTypes.Num(); i++)
	{
		float SpawnTrasnformRotation;

		if (i == 0)
		{
			SpawnTrasnformRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), worldPositions[i]).Yaw;
		}
		else
		{
			SpawnTrasnformRotation = UKismetMathLibrary::FindLookAtRotation(worldPositions[i - 1], worldPositions[i]).Yaw;
		}

		AActor* spawnMesh;

		FActorSpawnParameters param;
		SpawnActorUseClass(spawnMesh, meshTypes[i], param);

		spawnMesh->SetActorLocation(worldPositions[i] - FVector(0, 0, 90));
		spawnMesh->SetActorRotation(RotatorXYZ(0, 0, SpawnTrasnformRotation - 90));

		meshes.Add(spawnMesh);
	}
}

void ACBP_Projectile_Skill::SetVelocity(int skillIndex)
{
	FVector EndPosition = worldPositions[skillIndex];
	FVector StartPosition;

	if (skillIndex == 0)
	{
		StartPosition = GetActorLocation();
	}
	else
	{
		StartPosition = worldPositions[skillIndex - 1];
	}

	FVector velocity = (EndPosition - StartPosition);
	UKismetMathLibrary::Vector_Normalize(velocity);

	Projectile->Velocity = velocity * (Projectile->InitialSpeed);
	SetActorLocation(StartPosition);


}


void ACBP_Projectile_Skill::Play(bool const InSuccess, bool& Success)
{
	Super::Play(InSuccess, Success);

	bool succees;
	ThisClass::SetPointersToWorldPos(succees);

	if (succees == false)
	{
		Success = false;
		return;
	}

	SpawnMeshes();
	isPlay = true;
	curTime = 0.0f;
	curSkillIndex = 0;
	Projectile->Velocity = FVector(0, 0, 0);
	isDelay = true;
	Particle->SetVisibility(true);

	Success = true;

}

void ACBP_Projectile_Skill::Attack()
{
	worldStartPosition;
	// 위의 값을 이용해서 공격할 예정

	TArray<AActor*> overlapActors;

	UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(),
		worldStartPosition,
		attackLenght,
		{ EObjectTypeQuery::ObjectTypeQuery11 },
		nullptr,
		{ GetInstigator() },
		overlapActors
	);

	for (AActor* actor : overlapActors)
	{
		if (ACBP_Character* character = Cast<ACBP_Character>(actor))
		{
			ECharacterDamagedType damageType;
			F_Hp_Update_Value resultDamage;

			character->AddDamage(this, damageType, resultDamage);
			
			if (damageType == ECharacterDamagedType::Failling) continue;

			FVector particleLocation = character->GetActorLocation();

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
				particleLocation,
				fontColor,
				fontSize);
		}
	}

}

void ACBP_Projectile_Skill::SetSpawn(AActor* centerActor)
{
	AActor* result_CenterActor = centerActor;

	if (centerActor == nullptr)
		result_CenterActor = GetInstigator();

	if (result_CenterActor == nullptr) return;

	FVector InstigatorForward = result_CenterActor->GetActorForwardVector();
	FVector InstigatorUp = result_CenterActor->GetActorUpVector();
	FVector InstigatorRight = result_CenterActor->GetActorRightVector();

	worldStartPosition = InstigatorForward * centerStartPos.X +
		InstigatorUp * centerStartPos.Z +
		InstigatorRight * centerStartPos.Y;

	worldStartPosition += result_CenterActor->GetActorLocation();

	worldEndPosition = InstigatorForward * centerEndPos.X +
		InstigatorUp * centerEndPos.Z +
		InstigatorRight * centerEndPos.Y;

	worldEndPosition += result_CenterActor->GetActorLocation();

	SetActorLocation(worldStartPosition);

	startRotation = result_CenterActor->GetActorRotation();
	SetActorRotation(startRotation);

	isPlay = false;
}