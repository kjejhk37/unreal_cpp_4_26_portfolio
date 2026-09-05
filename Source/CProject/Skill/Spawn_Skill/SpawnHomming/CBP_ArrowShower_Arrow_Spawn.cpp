// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Spawn_Skill/SpawnHomming/CBP_ArrowShower_Arrow_Spawn.h"
#include "Particles/ParticleSystemComponent.h"
#include "Character/CBP_Character.h"

#include "Macro/KismetMacro.h"
#include "Macro/MyMacro.h"
#include "Macro/MathMacro.h"

#include "Logger/Logger.h"

ACBP_ArrowShower_Arrow_Spawn::ACBP_ArrowShower_Arrow_Spawn()
{
	CreateDefaultSubobjectAuto(particle);
	particle->SetupAttachment(GetRootComponent());

	particle->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));

	particle->Deactivate();
}

void ACBP_ArrowShower_Arrow_Spawn::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);
}

void ACBP_ArrowShower_Arrow_Spawn::BeginPlay()
{
	Super::BeginPlay();
}

void ACBP_ArrowShower_Arrow_Spawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isSkillStart == false) return;

	if (IsValid(temp) == false)
	{
		EndSkill();
	}
}

void ACBP_ArrowShower_Arrow_Spawn::Play(bool const InSuccess, bool & Success)
{
	Super::Play(InSuccess, Success);
	SetStart();
}

void ACBP_ArrowShower_Arrow_Spawn::SetSpawn(AActor* centerActor)
{
	Super::SetSpawn(centerActor);
}

void ACBP_ArrowShower_Arrow_Spawn::SetStart()
{
	KismetDelay(TEXT("Attack"), this, DelayTime);
	particle->Activate(true);
}

void ACBP_ArrowShower_Arrow_Spawn::SetEnd()
{
	particle->Deactivate();
}

void ACBP_ArrowShower_Arrow_Spawn::Attack()
{
	ACBP_Character* character = Cast<ACBP_Character>(GetInstigator());
	if (character == nullptr) return;

	character->SkillSpawn(skillClass, temp);
	ACBP_Spawn_HomingSkill* hommingSkill = Cast<ACBP_Spawn_HomingSkill>(temp);
	if (temp == nullptr) return;

	hommingSkill->damage = damage;
	hommingSkill->centerStartPos =FVector(0, 0, 1000);
	hommingSkill->centerEndPos = FVector(0, 0, 0);
	hommingSkill->delayTime = 0;
	hommingSkill->SetTargetTime = 0;
	hommingSkill->moveSpeed = 3500;
	hommingSkill->Trail_Start = FName("Trail_Start");
	hommingSkill->Trail_End = FName("Trail_End");

	hommingSkill->homingType = EHomingSkillType::endPosHoming;
	hommingSkill->attackType = EAttackType::NormalAttack;
	hommingSkill->attackHitType = EAttackHitType::HitAttack;
	hommingSkill->attackPushType = EAttackPushType::WeaponLocation;

	hommingSkill->SetSpawn(this);
	hommingSkill->SetActorScale3D(AttackScale);

	bool InSuccess = true;
	bool OutSuccess = false;
	hommingSkill->Play(InSuccess, OutSuccess);

	isSkillStart = true;
}

void ACBP_ArrowShower_Arrow_Spawn::EndSkill()
{
	DestroyActor(this);
}
