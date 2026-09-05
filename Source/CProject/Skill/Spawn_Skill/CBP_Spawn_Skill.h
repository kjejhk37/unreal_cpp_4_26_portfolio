// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/CBP_Skill.h"
#include "Interface/CBPI_SpawnMeshSkill.h"
#include "CBP_Spawn_Skill.generated.h"

UCLASS()
class CPROJECT_API ACBP_Spawn_Skill : public ACBP_Skill, public ICBPI_SpawnMeshSkill
{
	GENERATED_BODY()

public:
	ACBP_Spawn_Skill();
	void OnConstruction(const FTransform& Transform) override;
	//	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void Play(bool const InSuccess, bool& Success)override;
	void SetSpawn(AActor* centerActor) override;

protected:


};
