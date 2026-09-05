// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/Spawn_Skill/Simple/CBP_Simple_Spawn_Skill.h"
#include "CBP_Raven_Spawn.generated.h"


UCLASS()
class CPROJECT_API ACBP_Raven_Spawn : public ACBP_Simple_Spawn_Skill
{
	GENERATED_BODY()

public:
	ACBP_Raven_Spawn();
	void OnConstruction(const FTransform& Transform) override;
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void Play(bool const InSuccess, bool& Success)override;
	void SetMesh(EMeshType newMeshType)override;
	void SetSpawn(AActor* centerActor)override;

	void Attack() override;

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Set") int attackCount = 5;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Set") float playDelayTime = 0.25f;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Set") float endPlayDelayTime = 0.25f;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Set") float attackCoolTime = 1;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Set") TSubclassOf<ACBP_Spawn_Skill> AttackskillClass;

protected:
	UPROPERTY(VisibleAnywhere) class USphereComponent* AttackComponent;
	UPROPERTY(VisibleAnywhere) class UParticleSystemComponent* particle;

//	UPROPERTY(EditDefaultsOnly) class UParticleSystem* attackParticle;

	UFUNCTION(BlueprintCallable) void StartAttack();
	UFUNCTION(BlueprintCallable) void EndSkill();

	UFUNCTION() void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION() void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


protected:
	FTimerHandle Timer;
	TArray<AActor*> AttackActors;

};
