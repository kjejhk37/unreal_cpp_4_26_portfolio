// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/ProjectileType/CBP_SimpleProjectileSkill.h"
#include "Particle/CBP_Particle.h"
#include "CBP_Palatos_SimpleProjectile.generated.h"


UCLASS()
class CPROJECT_API ACBP_Palatos_SimpleProjectile : public ACBP_SimpleProjectileSkill
{
	GENERATED_BODY()
	
public:
	ACBP_Palatos_SimpleProjectile();

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	void Play(bool const InSuccess, bool& Success)override;

	void SetStart()override;
	void SetEnd() override;

	void SetSpawn(AActor* centerActor)override;


protected:
	UPROPERTY(VisibleAnywhere) class USphereComponent* AttackCollision;
	UPROPERTY(VisibleAnywhere) class USkeletalMeshComponent* PalatosMesh;
	UPROPERTY(VisibleAnywhere) class UStaticMeshComponent* ShieldMesh;
	UPROPERTY(VisibleAnywhere) class UStaticMeshComponent* SworldMesh;


	UFUNCTION() void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditDefaultsOnly) class UParticleSystem* attackParticle;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<ACBP_Particle> attackParticleActorClass;

	UPROPERTY(EditDefaultsOnly) FName shieldSocketName = FName("hand_l_Warior_Pair");
	UPROPERTY(EditDefaultsOnly) FName swordSocketName = FName("hand_r_Warior_Main");


	UPROPERTY() TArray<AActor*> AttackedActor;

	UFUNCTION() void ClearArray();
};
