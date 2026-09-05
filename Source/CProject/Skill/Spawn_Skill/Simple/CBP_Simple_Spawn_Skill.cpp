// Fill out your copyright notice in the Description page of Project Settings.


#include "CBP_Simple_Spawn_Skill.h"
#include "Macro/MyMacro.h"

ACBP_Simple_Spawn_Skill::ACBP_Simple_Spawn_Skill()
{

}

void ACBP_Simple_Spawn_Skill::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}

void ACBP_Simple_Spawn_Skill::BeginPlay()
{
	Super::BeginPlay();
}

void ACBP_Simple_Spawn_Skill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACBP_Simple_Spawn_Skill::Play(bool const InSuccess, bool& Success)
{
	Super::Play(InSuccess, Success);


}

void ACBP_Simple_Spawn_Skill::SetSpawn(AActor* centerActor)
{
	Super::SetSpawn(centerActor);
}

void ACBP_Simple_Spawn_Skill::SetMesh(EMeshType newMeshType)
{
	meshType = newMeshType;

	switch (meshType)
	{
	case EMeshType::StaticMesh:
		CreateDefaultSubobjectAuto(staticMesh);
		staticMesh->SetupAttachment(GetRootComponent());
		staticMesh->SetCollisionProfileName(FName("NoCollision"));
		break;
	case EMeshType::SkeletalMesh:
		CreateDefaultSubobjectAuto(skeletalMesh);
		skeletalMesh->SetupAttachment(GetRootComponent());
		skeletalMesh->SetCollisionProfileName(FName("NoCollision"));
		break;
	}
}