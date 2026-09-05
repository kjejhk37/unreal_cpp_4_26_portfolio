// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/Spawn_Skill/Simple/CBP_Simple_Spawn_Skill.h"
#include "Particle/CBP_Particle.h"
#include "CBP_AnimationType_SkillType.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API ACBP_AnimationType_SkillType : public ACBP_Simple_Spawn_Skill
{
	GENERATED_BODY()
	

public:
	ACBP_AnimationType_SkillType();
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
	UPROPERTY(EditDefaultsOnly, Category = "Set") class UCurveFloat* AnimationCurve;

	UPROPERTY(EditDefaultsOnly, Category = "Set") FVector meshStartRelativeLocation;
	UPROPERTY(EditDefaultsOnly, Category = "Set") FRotator meshStartRot;
	UPROPERTY(EditDefaultsOnly, Category = "Set") FVector meshStartScale = FVector(1,1,1);

	UPROPERTY(EditDefaultsOnly, Category = "Set") FVector centerStartLookVector;
//	UPROPERTY(EditDefaultsOnly, Category = "Set") float centerStartRoll;
	UPROPERTY(EditDefaultsOnly, Category = "Set") FRotator centerEndRotator;


	UPROPERTY(EditDefaultsOnly, Category = "Set") FVector centerStartScale = FVector(1, 1, 1);
	UPROPERTY(EditDefaultsOnly, Category = "Set") FVector centerEndScale = FVector(1, 1, 1);

	UPROPERTY(EditDefaultsOnly, Category = "Set") float animationTime;
	UPROPERTY(EditDefaultsOnly, Category = "Set") float delayTime;
	UPROPERTY(EditDefaultsOnly, Category = "Set") float destroyTime;

	UPROPERTY(EditDefaultsOnly, Category = "Set") int AttackNumber = 1;


	UPROPERTY(EditDefaultsOnly, Category = "Set") FName Trail_Start = FName("Center");
	UPROPERTY(EditDefaultsOnly, Category = "Set") FName Trail_End = FName("Trail_End");


protected:
	UPROPERTY(VisibleAnywhere) UParticleSystemComponent* particle;

	UFUNCTION() void Animation(float const Alpha);
	UFUNCTION() void AnimationEnd();
	UFUNCTION() void DestroyThisActor();

	UPROPERTY() class UTimelineComponent* animationTimeLine;

	// start, endPos는 이미 skll에 있음
	// startRot도 skill에 있음
//	FRotator endRotation;

	FVector startScale;
	FVector endScale;

	FRotator RotationSpeed;
	FRotator curRotator;

	bool animationStart = false;
	float ResetTime;
	int attackCount;
	bool isNoCollision = false;

protected:
	UFUNCTION(BlueprintCallable) void AnimationStart();
	UFUNCTION(BlueprintCallable) void ResetAttack();

protected:
	virtual void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)	PURE_VIRTUAL(ACBP_AnimationType_SkillType::OnComponentBeginOverlap, return;);

	UPROPERTY(VisibleAnywhere) class UShapeComponent* attackCollsiion;

	UPROPERTY() ECollisionType attackCollisionType = ECollisionType::None;

	UPROPERTY(EditDefaultsOnly) class UParticleSystem* attackParticle;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<ACBP_Particle> attackParticleActorClass;

	UPROPERTY(BlueprintReadOnly) TArray<AActor*> OverlapedActors;

};
