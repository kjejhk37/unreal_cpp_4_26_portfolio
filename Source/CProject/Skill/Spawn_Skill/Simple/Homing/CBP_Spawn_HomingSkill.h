// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/Spawn_Skill/Simple/CBP_Simple_Spawn_Skill.h"
#include "Enums/EWeapon.h"
#include "Particle/CBP_Particle.h"
#include "CBP_Spawn_HomingSkill.generated.h"

UCLASS()
class CPROJECT_API ACBP_Spawn_HomingSkill : public ACBP_Simple_Spawn_Skill
{
	GENERATED_BODY()

public:
	ACBP_Spawn_HomingSkill();
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

public:
	UPROPERTY(VisibleAnywhere) UParticleSystemComponent* particle;

	UPROPERTY(EditDefaultsOnly) class UParticleSystem* attackParticle;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<ACBP_Particle> attackParticleActorClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Set") FVector localLookVector;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Set") float centerStartRotRoll;

	UPROPERTY(EditDefaultsOnly, Category = "Set") FName Trail_Start = FName("Trail_Left");
	UPROPERTY(EditDefaultsOnly, Category = "Set") FName Trail_End = FName("Trail_Right");

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Set") float delayTime;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Set") float SetTargetTime = 1;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Set") float moveSpeed;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Set") EHomingSkillType homingType;

protected:
	UFUNCTION(BlueprintCallable) void StartHoming();
	UFUNCTION(BlueprintCallable) void SetTargetHoming();
	UFUNCTION(BlueprintCallable) void DestroyThisActor();

	UFUNCTION() FVector GetHommingTargetLocation();

protected:
	UFUNCTION() void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

protected:
	UPROPERTY(VisibleAnywhere) class UShapeComponent* attackComponent;

	ECollisionType attackCollisionType = ECollisionType::Capsule;
	USceneComponent* tempTarget;

	bool isHoming = false;

	// 타겟 조정 완료
	bool TargetCompleted = false;
	float rotationValue = 360;

};
