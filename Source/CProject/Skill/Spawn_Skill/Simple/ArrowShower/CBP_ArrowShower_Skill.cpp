// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Spawn_Skill/Simple/ArrowShower/CBP_ArrowShower_Skill.h"
#include "Particles/ParticleSystemComponent.h"
#include "Character/CBP_Character.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

#include "Macro/MyMacro.h"
#include "Macro/KismetMacro.h"
#include "Macro/MathMacro.h"

#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"

#include "Logger/Logger.h"

ACBP_ArrowShower_Skill::ACBP_ArrowShower_Skill()
{
	CreateDefaultSubobjectAuto(particle);
	particle->SetupAttachment(GetRootComponent());
}


void ACBP_ArrowShower_Skill::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ACBP_ArrowShower_Skill::BeginPlay()
{
	Super::BeginPlay();

}

void ACBP_ArrowShower_Skill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isPlay == false) return;

	curTime += DeltaTime;

	ACBP_Character* character = Cast<ACBP_Character>(GetInstigator());
	if (character == nullptr) return;

	TArray<int> removeAtTemp;

	for (int i = 0 ; i < Arrows.Num(); i++)
	{
		F_ArrowStruct arrow = Arrows[i];

		if (arrow.SpawnTime >= curTime) continue;

		if (arrow.skillClass != nullptr)
		{
			ACBP_Skill* skill;
			character->SkillSpawn(arrow.skillClass, skill);
			ACBP_ArrowShower_Arrow_Spawn* arrowSkill = Cast<ACBP_ArrowShower_Arrow_Spawn>(skill);
			if (arrowSkill == nullptr) return;

			FVector WorldPos = ActorLocalToWorldLocation(this,arrow.SpawnPos);

			skill->SetActorLocation(WorldPos);
			skill->damage = damage;
			arrowSkill->AttackScale = arrow.SpawnScale;

			bool InSuccess = true;
			bool OutSuccess = false;
			skill->Play(InSuccess, OutSuccess);
		}

		removeAtTemp.Add(i);
	}

	for (int i : removeAtTemp)
	{
		Arrows.RemoveAt(i);
	}


	if (Arrows.Num() == 0)
	{
		DestroyActor(this);
	}
}

void ACBP_ArrowShower_Skill::Play(bool const InSuccess, bool& Success)
{
	Super::Play(InSuccess, Success);

	isPlay = true;
	curTime = 0;
}

void ACBP_ArrowShower_Skill::SetMesh(EMeshType newMeshType)
{
	Super::SetMesh(newMeshType);
}

void ACBP_ArrowShower_Skill::SetSpawn(AActor* centerActor)
{
	Super::SetSpawn(centerActor);
}
