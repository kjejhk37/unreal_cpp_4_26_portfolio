// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/AttachSkill/CBP_Attach_Skill.h"
#include "Particles/ParticleSystemComponent.h"
#include "Character/CBP_Character.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

#include "Macro/MyMacro.h"
#include "Macro/KismetMacro.h"

#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"

#include "Logger/Logger.h"

ACBP_Attach_Skill::ACBP_Attach_Skill()
{
	CreateDefaultSubobjectAuto(particle);
	particle->SetupAttachment(GetRootComponent());

}


void ACBP_Attach_Skill::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ACBP_Attach_Skill::BeginPlay()
{
	Super::BeginPlay();

	if (Timer == FTimerHandle())
	{
		GetWorld()->GetTimerManager().SetTimer
		(
			Timer, this, &ThisClass::Attack, attackCoolTime, true, 0
		);

		SetPauseTimer(Timer);
	}


	KismetDelay(TEXT("EndSkill"), this, playTime);
}

void ACBP_Attach_Skill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACBP_Attach_Skill::Play(bool const InSuccess, bool& Success)
{
	Super::Play(InSuccess, Success);

	StartAttack();

//	KismetDelay(TEXT("StartAttack"), this, playDelayTime);
}

void ACBP_Attach_Skill::Attack()
{

	ACBP_Character* instigatorCharacter = Cast<ACBP_Character>(GetInstigator());
	if (instigatorCharacter == nullptr) return;

	if (AttackskillClass == nullptr) return;

	ACBP_Skill* attackSkill;

	instigatorCharacter->SkillSpawn(AttackskillClass, attackSkill,skillType);
	attackSkill->damage = damage;

	attackSkill->SetSpawn(this);

	bool inSuccess = true;
	bool outSuccess = false;
	attackSkill->Play(inSuccess, outSuccess);

	attackCount--;

	if (attackCount <= 0)
	{
		SetPauseTimer(Timer);

		particle->Deactivate();

		KismetDelay(TEXT("EndSkill"), this, endPlayDelayTime);
	}

}

void ACBP_Attach_Skill::StartAttack()
{

	if (Timer == FTimerHandle())
	{
		GetWorld()->GetTimerManager().SetTimer
		(
			Timer, this, &ThisClass::Attack, attackCoolTime, true, 0
		);
	}
	else
	{
		SetUnPauseTimer(Timer);
	}
}

void ACBP_Attach_Skill::EndSkill()
{
	DestroyActor(this);
}

void ACBP_Attach_Skill::SetSpawn(AActor* centerActor)
{
//	Super::SetSpawn(centerActor);

	ACBP_Character* character = Cast<ACBP_Character>(GetInstigator());
	if (character == nullptr) return;

	FAttachmentTransformRules const Rule(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(character->center, Rule);

	FRotator rotator = FRotator(0,0,0);
	rotator.Roll = centerStartRoll;

	SetActorRelativeRotation(rotator);

}

