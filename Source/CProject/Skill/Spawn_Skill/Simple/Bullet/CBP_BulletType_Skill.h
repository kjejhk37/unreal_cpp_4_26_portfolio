// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/Spawn_Skill/Simple/CBP_Simple_Spawn_Skill.h"
#include "Particle/CBP_Particle.h"
#include "CBP_BulletType_Skill.generated.h"


UCLASS()
class CPROJECT_API ACBP_BulletType_Skill : public ACBP_Simple_Spawn_Skill
{
	GENERATED_BODY()

public:
	ACBP_BulletType_Skill();
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

	// ½ò¶§ÀÇ socket
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Socket") FName shotSocket = FName("ShotSocket");

protected:
	UPROPERTY(VisibleAnywhere) class UParticleSystemComponent* Particle;

	UPROPERTY(VisibleAnywhere) class UProjectileMovementComponent* Projectile;
	UPROPERTY(VisibleAnywhere) class UShapeComponent* attackCollsiion;
	UPROPERTY(VisibleAnywhere) ECollisionType attackCollisionType = ECollisionType::Capsule;


	UFUNCTION() void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditDefaultsOnly) class UParticleSystem* attackParticle;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<ACBP_Particle> attackParticleActorClass;

	UFUNCTION() void ArrowDelete();


private:
	float bulletSpeed = 5000;	
};
