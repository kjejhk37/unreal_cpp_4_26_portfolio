// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Spawn_Skill/Simple/ArrowShower/CBP_Carpet_Bombing_Skill.h"
#include "Particles/ParticleSystem.h"

#include "Macro/KismetMacro.h"

ACBP_Carpet_Bombing_Skill::ACBP_Carpet_Bombing_Skill()
{

}

void ACBP_Carpet_Bombing_Skill::BeginPlay()
{
	Super::BeginPlay();

	Arrows.Empty();

	float start_Y = (YLenght * (LineNum - 1)) / 2;

	for (int i = 0; i < Count; i++)
	{
		for (int j = 0; j < LineNum; j++)	// ¶óÀÎ ¼ö
		{
			F_ArrowStruct addStruct;

			addStruct.skillClass = skillClass;
			addStruct.SpawnTime = ArrowFrequencyTime * (float)i;

			FVector pos(0, 0, 0);
			pos.Y = (j * YLenght) - start_Y;
			pos.X = i * XLenght;

			addStruct.SpawnPos = pos;
			addStruct.SpawnScale = skillScale;

			Arrows.Add(addStruct);
		}
	}
}
