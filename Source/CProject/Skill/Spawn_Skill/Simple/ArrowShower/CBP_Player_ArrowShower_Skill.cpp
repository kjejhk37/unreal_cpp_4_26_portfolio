// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Spawn_Skill/Simple/ArrowShower/CBP_Player_ArrowShower_Skill.h"
#include "Particles/ParticleSystem.h"

#include "Macro/KismetMacro.h"

ACBP_Player_ArrowShower_Skill::ACBP_Player_ArrowShower_Skill()
{

}

void ACBP_Player_ArrowShower_Skill::BeginPlay()
{
	Super::BeginPlay();

	Arrows.Empty();

	for (int i = 0; i < Count; i++)
	{
		F_ArrowStruct addStruct;

		addStruct.skillClass = skillClass;
		addStruct.SpawnTime = ArrowFrequencyTime * (float)i;

		FVector pos;
		float Range = rand() % 300;
		float Degree = rand() % 360;

		pos.X = Range * UKismetMathLibrary::DegCos(Degree);
		pos.Y = Range * UKismetMathLibrary::DegSin(Degree);
		pos.Z = 0;

		addStruct.SpawnPos = pos;
		addStruct.SpawnScale = skillScale;

		Arrows.Add(addStruct);
	}
}