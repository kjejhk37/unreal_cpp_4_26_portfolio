// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/Spawn_Skill/Simple/CBP_Simple_Spawn_Skill.h"

#include "Skill/Spawn_Skill/SpawnHomming/CBP_ArrowShower_Arrow_Spawn.h"

#include "CBP_ArrowShower_Skill.generated.h"


USTRUCT(BlueprintType)
struct F_ArrowStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TSubclassOf<ACBP_ArrowShower_Arrow_Spawn> skillClass;

	UPROPERTY(EditAnywhere) float SpawnTime;
	UPROPERTY(EditAnywhere) FVector SpawnPos;
	UPROPERTY(EditAnywhere) FVector SpawnScale = FVector(1,1,1);


};

UCLASS()
class CPROJECT_API ACBP_ArrowShower_Skill : public ACBP_Simple_Spawn_Skill
{
	GENERATED_BODY()

public:
	ACBP_ArrowShower_Skill();
	void OnConstruction(const FTransform& Transform) override;
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void Play(bool const InSuccess, bool& Success)override;
	void SetMesh(EMeshType newMeshType)override;
	void SetSpawn(AActor* centerActor)override;

public:
	UPROPERTY() TArray<F_ArrowStruct> Arrows;


protected:
	UPROPERTY(VisibleAnywhere) class UParticleSystemComponent* particle;

private:
	float curTime = 0;
	bool isPlay = false;

};
