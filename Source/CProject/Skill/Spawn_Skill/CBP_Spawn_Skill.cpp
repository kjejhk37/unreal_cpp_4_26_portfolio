// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Spawn_Skill/CBP_Spawn_Skill.h"
#include "Kismet/KismetMathLibrary.h"


ACBP_Spawn_Skill::ACBP_Spawn_Skill()
{

}

void ACBP_Spawn_Skill::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}

void ACBP_Spawn_Skill::BeginPlay()
{
	Super::BeginPlay();

}

void ACBP_Spawn_Skill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACBP_Spawn_Skill::Play(bool const InSuccess, bool& Success)
{
	Super::Play(InSuccess, Success);

	Success = InSuccess;
}

void ACBP_Spawn_Skill::SetSpawn(AActor* centerActor)
{
	Super::SetSpawn(centerActor);
}