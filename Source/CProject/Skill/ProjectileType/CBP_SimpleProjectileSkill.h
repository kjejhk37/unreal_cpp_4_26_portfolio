// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/CBP_Skill.h"
#include "CBP_SimpleProjectileSkill.generated.h"

UCLASS()
class CPROJECT_API ACBP_SimpleProjectileSkill : public ACBP_Skill
{
	GENERATED_BODY()

public:
	ACBP_SimpleProjectileSkill();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	void Play(bool const InSuccess, bool& Success)override;

	void SetStart()override;
	void SetEnd() override;


public:
	UFUNCTION(BlueprintCallable, Category = "Set") void SetPointersToWorldPos(AActor* centerActor,bool& success);
	UFUNCTION(BlueprintCallable, Category = "Set") void SpawnMeshes();
	UFUNCTION(BlueprintCallable, Category = "Set") void SetVelocity();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Setting")	float delayTime;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Setting")	FVector startPointer = FVector(0,0,0);
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Setting")	FVector endPointer;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Setting")	TSubclassOf<AActor> meshType;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Setting")	float moveSpeed;

protected:
	UPROPERTY(VisibleAnywhere) class UParticleSystemComponent* Particle;
	UPROPERTY(VisibleAnywhere) class UArrowComponent* Arrow;

	UPROPERTY(VisibleAnywhere) class UProjectileMovementComponent* Projectile;
	
	UPROPERTY(BlueprintReadOnly) AActor* mesh;

	UPROPERTY(BlueprintReadOnly) FVector startPosition;
	UPROPERTY(BlueprintReadOnly) FVector endPosition;
	UPROPERTY(BlueprintReadOnly) float playTime;

	UPROPERTY(BlueprintReadOnly) bool isPlay = false;
	UPROPERTY(BlueprintReadOnly) bool isDelay = true;
	UPROPERTY(BlueprintReadOnly) float curPlayTime = 0;
	
};
