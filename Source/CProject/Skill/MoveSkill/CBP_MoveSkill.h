// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/CBP_Skill.h"
#include "Particle/CBP_Particle.h"
#include "CBP_MoveSkill.generated.h"


UCLASS()
class CPROJECT_API ACBP_MoveSkill : public ACBP_Skill
{
	GENERATED_BODY()

public:
	ACBP_MoveSkill();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;


public:
	void Play(bool const InSuccess, bool& Success)override;
	void SetSpawn(AActor* centerActor)override;

	void SetStart()override;
	void SetEnd() override;


public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly) 	float DelayTime = 0.0f;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly) 	float PlayTime = 1.0f;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly) 	FVector upPos = FVector(0, 0, 100);
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly) 	FVector underPos = FVector(0, 0, -100);
protected:
	UPROPERTY(VisibleAnywhere) class USphereComponent* AttackCollision;
	UPROPERTY(VisibleAnywhere) class UParticleSystemComponent* particle;

	UFUNCTION(BlueprintCallable) void StartMoveSkill();

	bool isPlay = false;
	float Speed;
	FVector Velocity;
	float curPlayTime = 0;

protected:
	UFUNCTION() void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditDefaultsOnly) class UParticleSystem* attackParticle;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<ACBP_Particle> attackParticleActorClass;
	UPROPERTY() TArray<AActor*> OverrlapedActors;

};
