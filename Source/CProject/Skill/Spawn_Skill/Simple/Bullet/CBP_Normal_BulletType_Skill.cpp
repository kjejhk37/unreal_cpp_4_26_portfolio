// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Spawn_Skill/Simple/Bullet/CBP_Normal_BulletType_Skill.h"

#include "Particles/ParticleSystemComponent.h"
#include "Components/CapsuleComponent.h"

#include "Macro/MathMacro.h"

ACBP_Normal_BulletType_Skill::ACBP_Normal_BulletType_Skill()
{
	SetMesh(EMeshType::StaticMesh);
	
	Particle->SetRelativeRotation(RotatorXYZ(0, 90, 0));
	staticMesh->SetRelativeRotation(RotatorXYZ(0, -90, 0));
	Cast<UCapsuleComponent>(attackCollsiion)->SetCapsuleHalfHeight(5);
	Cast<UCapsuleComponent>(attackCollsiion)->SetCapsuleRadius(2);
}
