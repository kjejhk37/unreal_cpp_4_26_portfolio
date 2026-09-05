// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/ProjectileType/CBP_SimpleProjectileSkill.h"
#include "Particle/CBP_Particle.h"
#include "CBP_Raven_ProjectileAttack.generated.h"


UCLASS()
class CPROJECT_API ACBP_Raven_ProjectileAttack : public ACBP_SimpleProjectileSkill
{
	GENERATED_BODY()

public:
	ACBP_Raven_ProjectileAttack();

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	void Play(bool const InSuccess, bool& Success)override;

	void SetStart()override;
	void SetEnd() override;

protected:
	UPROPERTY(VisibleAnywhere) class USphereComponent* AttackCollision;
	UPROPERTY(VisibleAnywhere) class USkeletalMeshComponent* RavenMesh;

	UFUNCTION() void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditDefaultsOnly) class UParticleSystem* attackParticle;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<ACBP_Particle> attackParticleActorClass;

	UPROPERTY() TArray<AActor*> AttackedActor;

	UFUNCTION() void ClearArray();

};
