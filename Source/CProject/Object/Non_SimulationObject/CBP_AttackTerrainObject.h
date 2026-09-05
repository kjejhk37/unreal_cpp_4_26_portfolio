// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Non_SimulationObject/CBP_Non_SimulationObject.h"
#include "Interface/CBPI_CanGetAttackDataObject.h"

#include "CBP_AttackTerrainObject.generated.h"


UCLASS()
class CPROJECT_API ACBP_AttackTerrainObject : public ACBP_Non_SimulationObject , public ICBPI_CanGetAttackDataObject
{
	GENERATED_BODY()

public:
	ACBP_AttackTerrainObject();

	virtual void BeginPlay() override;
	virtual void WorkAttackTerrain() override;
protected:
	void Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType) override;

public:
	UFUNCTION() void SetClearAttackedActors();
	UFUNCTION() void StartDelay();
	
protected:
	UPROPERTY(VisibleAnywhere) class USceneComponent* center;
	UPROPERTY(VisibleAnywhere) class UShapeComponent* attackComponent;
	UPROPERTY(VisibleAnywhere) class UParticleSystemComponent* particleComponent;

	UPROPERTY(EditDefaultsOnly) class UParticleSystem* particle;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<class ACBP_Particle> particleActorClass;

	UPROPERTY(BlueprintReadOnly) ECollisionType attackCollisionType = ECollisionType::Box;

	void SpawnParticle(FVector particleLocation);
	void SpawnTextActor(FString string, FVector Location, FVector fontColor, float fontSize, float outlineFontSize);

	float attackCoolTime = 0.25f;
	TArray<AActor*> attackedActors;

protected:
	UFUNCTION() void OnAttackComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, Category = "Set") FVector inEndLocation = FVector(0,0,0);
	UPROPERTY(EditAnywhere, Category = "Set") FRotator inEndRotator = FRotator(0,0,0);
	UPROPERTY(EditAnywhere, Category = "Set") float playTime = 3;


	UPROPERTY(EditAnywhere, Category = "Set") F_Hp_Update_Value damage;
	UPROPERTY(EditAnywhere, Category = "Set") EAttackType attackType = EAttackType::NormalAttack;

	UPROPERTY(EditAnywhere, Category = "Set") EAttackHitType attackHitType = EAttackHitType::DownAttack;
	UPROPERTY(EditAnywhere, Category = "Set") FVector pushVector;

	UPROPERTY(EditAnywhere, Category = "Set") EAttackPushType attackPushType = EAttackPushType::WeaponLocation;
	UPROPERTY(EditAnywhere, Category = "Set") EGuardSerchType guardSerchType = EGuardSerchType::Actor;

	FVector startLocation;
	FRotator startRotator;

	FVector endLocation;
	FRotator endRotaotr;

public:
	void GetInstigatorcharacter(ACBP_Character*& outCharacter)override;
	void GetFinalDamage(F_Hp_Update_Value& outDamage) override;

	void GetAttackType(EAttackType& outAttackType) override;
	void GetAttackHitType(EAttackHitType& outAttackHitType) override;

	void GetPushVector(FVector& outPushVector) override;
	void GetAttackPushType(EAttackPushType& outAttackPushType) override;

	void GetGuardSerchType(EGuardSerchType& outGuardSerchType) override;

private:
	bool isNoCollision = false;

protected:
	UPROPERTY()
		class UTimelineComponent* AnimationTimeLine;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
		class UCurveFloat* BlendCurveOnAnimation;

private:
	UFUNCTION()
		void Animation(float const Alpha);

};
