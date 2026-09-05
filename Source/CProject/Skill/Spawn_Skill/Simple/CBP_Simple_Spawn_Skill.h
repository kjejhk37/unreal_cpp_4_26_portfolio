// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/Spawn_Skill/CBP_Spawn_Skill.h"
#include "Enums/EObject.h"
#include "CBP_Simple_Spawn_Skill.generated.h"

UCLASS()
class CPROJECT_API ACBP_Simple_Spawn_Skill : public ACBP_Spawn_Skill
{
	GENERATED_BODY()
	
public:
	ACBP_Simple_Spawn_Skill();
	void OnConstruction(const FTransform& Transform) override;
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void Play(bool const InSuccess, bool& Success)override;
	void SetMesh(EMeshType newMeshType)override;
	void SetSpawn(AActor* centerActor)override;

protected:
	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* staticMesh;
	UPROPERTY(VisibleAnywhere) USkeletalMeshComponent* skeletalMesh;

	UPROPERTY(BlueprintReadOnly, Category = "Set") EMeshType meshType;
};
