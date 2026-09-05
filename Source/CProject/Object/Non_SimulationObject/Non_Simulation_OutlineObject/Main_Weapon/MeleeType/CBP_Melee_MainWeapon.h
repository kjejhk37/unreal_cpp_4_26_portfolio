// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/Main_Weapon/CBP_MainWeapon.h"
#include "Interface/CBPI_Trail_Particle_Weapon.h"
#include "Particle/CBP_Particle.h"
#include "CBP_Melee_MainWeapon.generated.h"

UCLASS()
class CPROJECT_API ACBP_Melee_MainWeapon : public ACBP_MainWeapon, public ICBPI_Trail_Particle_Weapon
{
	GENERATED_BODY()

public:
	ACBP_Melee_MainWeapon();
	void OnConstruction(const FTransform& Transform) override;
protected:
	void Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType) override;
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	void Activate(bool InSuccess, bool& OutSuccess) override;
	void DeActivate(bool InSuccess, bool& OutSuccess) override;

	void TrailParticleActivate() override;
	void TrailParticleDeActivate() override;

protected:
	UPROPERTY(VisibleAnywhere) UParticleSystemComponent* particleSystem;
	UPROPERTY(VisibleAnywhere) UShapeComponent* attackComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Type") ECollisionType attackCollisionType = ECollisionType::Capsule;

	UPROPERTY(BlueprintReadOnly, Category = "Socket") FName Trail_Start_Socket;
	UPROPERTY(BlueprintReadOnly, Category = "Socket") FName Trail_End_Socket;

protected:
	virtual void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) PURE_VIRTUAL(ACBP_Melee_MainWeapon::OnComponentBeginOverlap, return;);

	UPROPERTY(EditDefaultsOnly, Category = "Particle") class UParticleSystem* attackParticle;
	UPROPERTY(EditDefaultsOnly, Category = "Particle") TSubclassOf<ACBP_Particle> attackParticleActorClass;

	UPROPERTY(BlueprintReadOnly) TArray<AActor*> OverlapedActors;

	
};
