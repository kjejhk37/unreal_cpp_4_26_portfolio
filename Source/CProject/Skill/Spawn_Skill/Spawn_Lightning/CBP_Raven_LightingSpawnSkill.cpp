// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Spawn_Skill/Spawn_Lightning/CBP_Raven_LightingSpawnSkill.h"
#include "Particles/ParticleSystemComponent.h"


ACBP_Raven_LightingSpawnSkill::ACBP_Raven_LightingSpawnSkill()
{
	particle->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));

}