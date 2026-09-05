// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/CBP_Skill.h"
#include "Particle/CBP_Particle.h"
#include "CBP_Projectile_Skill.generated.h"

UCLASS()
class CPROJECT_API ACBP_Projectile_Skill : public ACBP_Skill
{
	GENERATED_BODY()

public:
	ACBP_Projectile_Skill();
	void OnConstruction(const FTransform& Transform) override;
	//	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void Play(bool const InSuccess, bool& Success)override;

	void SetSpawn(AActor* centerActor)override;

public:
	UFUNCTION(BlueprintCallable, Category = "Set") void SetPointersToWorldPos(bool& success);
	UFUNCTION(BlueprintCallable, Category = "Set") void SpawnMeshes();
	UFUNCTION(BlueprintCallable, Category = "Set") void SetVelocity(int skillIndex);

	UFUNCTION(BlueprintCallable, Category = "Attack") void Attack();
	UFUNCTION() void DestroyThisActor();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Setting")  TArray<float> delayTimes;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Setting")  TArray<FVector> localPointers;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Setting")  TArray<TSubclassOf<AActor>> meshTypes;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Setting")  float attackLenght = 500;

protected:
	UPROPERTY(VisibleAnywhere) class UParticleSystemComponent* Particle;
	UPROPERTY(VisibleAnywhere) class UArrowComponent* Arrow;

	UPROPERTY(VisibleAnywhere) class UProjectileMovementComponent* Projectile;


	UPROPERTY(BlueprintReadOnly, Category = "Pointers") TArray<FVector> worldPositions;

	UPROPERTY(BlueprintReadOnly, Category = "Times") int curSkillIndex;
	UPROPERTY(BlueprintReadOnly, Category = "Times") float curTime;
	UPROPERTY(BlueprintReadOnly, Category = "Times") TArray<float> Times;

	UPROPERTY(BlueprintReadOnly, Category = "Meshes")  TArray<AActor*> meshes;

	UPROPERTY(BlueprintReadOnly, Category = "Temp")  bool isPlay = false;
	UPROPERTY(BlueprintReadOnly, Category = "Temp")  bool isDelay;

	UPROPERTY(EditDefaultsOnly) class UParticleSystem* attackParticle;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<ACBP_Particle> attackParticleActorClass;

};
