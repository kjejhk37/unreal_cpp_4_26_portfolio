// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Struct/SWeapon.h"
#include "CBP_Particle.generated.h"

UCLASS()
class CPROJECT_API ACBP_Particle : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBP_Particle();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable) void SetParticlesBase(TArray<F_ParticleActorData> data);
	UFUNCTION(BlueprintCallable) void Play();
	
	UFUNCTION(BlueprintCallable) void start();
	UFUNCTION(BlueprintCallable) void end();
	UFUNCTION(BlueprintCallable) void StartNextParticle();
protected:
	UPROPERTY(VisibleAnywhere) class USceneComponent* center;
	UPROPERTY(VisibleAnywhere) class UParticleSystemComponent* particle;

	UPROPERTY(EditDefaultsOnly) TArray<F_ParticleActorData> nextParticles;
	UPROPERTY(EditDefaultsOnly) float PlayTime;
	UPROPERTY(EditDefaultsOnly) float StartDelayTime;
	UPROPERTY(EditDefaultsOnly) float EndDelayTime;


};
