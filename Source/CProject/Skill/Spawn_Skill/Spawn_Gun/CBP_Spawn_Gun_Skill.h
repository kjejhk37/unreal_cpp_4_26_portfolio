// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/Spawn_Skill/CBP_Spawn_Skill.h"
#include "CBP_Spawn_Gun_Skill.generated.h"


UCLASS()
class CPROJECT_API ACBP_Spawn_Gun_Skill : public ACBP_Spawn_Skill
{
	GENERATED_BODY()

public:
	ACBP_Spawn_Gun_Skill();
	void OnConstruction(const FTransform& Transform) override;
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void Play(bool const InSuccess, bool& Success)override;
	void SetSpawn(AActor* centerActor) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Shot") void Shot(bool isDelay);

	UFUNCTION() void GunOnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Setting") float delayTime;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Setting") int attackCount;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Setting") float attackCoolTime;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Setting") float attackLength;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Setting") float endPlaySpeed;

	UPROPERTY(VisibleAnywhere) USkeletalMeshComponent* GunMesh;
protected:
	UFUNCTION(BlueprintCallable) void CheckEnd();
	UFUNCTION(BlueprintCallable) void SetEnd();
	UFUNCTION(BlueprintCallable) void GunShot();
	UFUNCTION(BlueprintCallable) void LookAtTarget();


protected:

	UPROPERTY(BlueprintReadOnly, Category = "Time") float endPlayTime;
	UPROPERTY(BlueprintReadOnly, Category = "Time") bool endPlay;
	UPROPERTY(BlueprintReadOnly, Category = "Time") float playTime;

	UPROPERTY(BlueprintReadOnly, Category = "Time") bool stopShot;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Set") UAnimMontage* ShotMontage;

public:
	UFUNCTION(BlueprintCallable) void ShotDelegate();
	UFUNCTION(BlueprintCallable) void DestroyThisActor();

private:
	bool isCharacterSkillStart = false;
};
