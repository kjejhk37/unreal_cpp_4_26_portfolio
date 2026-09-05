// Fill out your copyright notice in the Description page of Project Settings.


#include "CBP_Skill.h"
#include "Character/CBP_Character.h"

#include "Particle/CBP_Particle.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

#include "Macro/MyMacro.h"
#include "Macro/KismetMacro.h"

#include "UI/CBP_TextActor.h"

ACBP_Skill::ACBP_Skill()
{
	PrimaryActorTick.bCanEverTick = true;

	CreateDefaultSubobjectAuto(center);
	SetRootComponent(center);
}

void ACBP_Skill::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACBP_Skill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACBP_Skill::Play(bool const InSuccess, bool& Success)
{
	Success = InSuccess;
}

void ACBP_Skill::SetSpawn(AActor* centerActor)
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
	startRotation.Roll += centerStartRoll;

	SetActorRotation(startRotation);

	if (ACBP_Character* character = Cast<ACBP_Character>(GetInstigator()))
	{
		Target = character->target;
	}
}

void ACBP_Skill::SetStart()
{
	// 스킬이 시작되었을때 즉 한번 딜레이를 하고 나서 진짜로 스킬이 시작되었을떄 발동
}
void ACBP_Skill::SetEnd()
{
	// 스킬이 끝났을떄 발동
}

void ACBP_Skill::SpawnTextActor(FString string, FVector Location, FVector fontColor, float fontSize, float outlineFontSize)
{
	ACBP_TextActor* textActor;
	FActorSpawnParameters param;

	SpawnActorUseClass(textActor, ACBP_TextActor::StaticClass(), param);
	textActor->SetActorLocation(Location);

	textActor->SetTextFont(fontSize);
	textActor->SetTextOutlineFont(outlineFontSize);
	textActor->SetTextBox(string, fontColor);
}

void ACBP_Skill::SpawnAttackParticle(UParticleSystem* inAttackParticle, TSubclassOf<ACBP_Particle> inAttackParticleActorClass, FVector particleLocation)
{
	if (inAttackParticle != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), inAttackParticle, particleLocation,
			FRotator(0, 0, 0), FVector(1, 1, 1), true);
	}

	if (inAttackParticleActorClass != nullptr)
	{
		ACBP_Particle* particleActor;
		FActorSpawnParameters param;

		SpawnActorUseClass(particleActor, inAttackParticleActorClass, param);
		particleActor->SetActorLocation(particleLocation);

		F_ParticleActorData data;
		data.EndDelayTime = 0;
		data.StartDelayTime = 0;

		particleActor->SetParticlesBase({ data });
		particleActor->Play();
	}
}


void ACBP_Skill::GetInstigatorcharacter(ACBP_Character*& outCharacter) { outCharacter = Cast<ACBP_Character>(GetInstigator()); }
void ACBP_Skill::GetFinalDamage(F_Hp_Update_Value& outDamage) { outDamage = damage; }
void ACBP_Skill::GetAttackType(EAttackType& outAttackType) { outAttackType = attackType; }
void ACBP_Skill::GetAttackHitType(EAttackHitType& outAttackHitType) { outAttackHitType = attackHitType; }
void ACBP_Skill::GetPushVector(FVector& outPushVector) { outPushVector = pushVector; }
void ACBP_Skill::GetAttackPushType(EAttackPushType& outAttackPushType) { outAttackPushType = attackPushType; }
void ACBP_Skill::GetGuardSerchType(EGuardSerchType& outGuardSerchType) { outGuardSerchType = guardSerchType; }
void ACBP_Skill::GetCamp(ECamp& outCamp) { if (ACBP_Character* character = Cast<ACBP_Character>(GetInstigator())) { outCamp = character->camp; } else { outCamp = ECamp::Neutrality; } }