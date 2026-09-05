// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/Spawn_Skill/Simple/CBP_Simple_Spawn_Skill.h"
#include "Particle/CBP_Particle.h"
#include "CBP_Player_ArrowShot.generated.h"


UCLASS()
class CPROJECT_API ACBP_Player_ArrowShot : public ACBP_Simple_Spawn_Skill
{
	GENERATED_BODY()

public:
	ACBP_Player_ArrowShot();
	void OnConstruction(const FTransform& Transform) override;
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void Play(bool const InSuccess, bool& Success)override;
	void SetMesh(EMeshType newMeshType)override;
	void SetSpawn(AActor* centerActor)override;

	void SetStart()override;
	void SetEnd() override;

	// ΩÓ±‚¿¸¿« socket
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Socket") FName shotReadySocket = FName("Bow_shotReadySocket");
	// ΩÚ∂ß¿« socket
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Socket") FName shotSocket = FName("Bow_shotSocket");
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Socket") FName trail_Start = FName("Trail_Start");
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Socket") FName trail_End = FName("Trail_End");


protected:
	UPROPERTY(VisibleAnywhere) class UParticleSystemComponent* Particle;
	UPROPERTY(VisibleAnywhere) class UArrowComponent* Arrow;

	UPROPERTY(VisibleAnywhere) class UProjectileMovementComponent* Projectile;
	UPROPERTY(VisibleAnywhere) class USphereComponent* attackCollsiion;

	UFUNCTION() void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditDefaultsOnly) class UParticleSystem* attackParticle;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<ACBP_Particle> attackParticleActorClass;

	UFUNCTION() void ArrowDelete();


private:
	float arrowSpeed = 3500;
	FVector targetLocation;
	
};
