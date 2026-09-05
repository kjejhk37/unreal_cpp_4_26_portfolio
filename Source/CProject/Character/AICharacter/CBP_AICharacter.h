// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CBP_Character.h"


#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"

#include "Macro/IncludeMacro.h"

#include MainWeaponPath
#include PairWeaponPath

#include "Object/SimulationObject/Interaction_Object/Case/CBP_WeaponCase.h"

#include "CBP_AICharacter.generated.h"


UCLASS()
class CPROJECT_API ACBP_AICharacter : public ACBP_Character
{
	GENERATED_BODY()

public:
	ACBP_AICharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void PossessedBy(AController* NewController) override;

	virtual void ActionDropping(bool& Success) override;
	virtual void UpdateHpWidget()override;
	virtual void AddDamage(AActor* WeaponActor, ECharacterDamagedType& damageType, F_Hp_Update_Value& resultDamage)override;

	virtual void SetDie() override;

	UPROPERTY(VisibleAnywhere) class UWidgetComponent* Guard_GaugeBar;


	UFUNCTION(BlueprintCallable, Category = "AI") void SetAIPerception();
	UFUNCTION(BlueprintCallable) void AI_OnTargetPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus);
	UFUNCTION(BlueprintCallable) void AI_OnPerceptionUpdate(const TArray<AActor*>& UpdatedActors);

	UFUNCTION(BlueprintCallable) void SpawnBaseWeapon(TSubclassOf<ACBP_MainWeapon> mainWeaponClass,TSubclassOf<ACBP_PairWeapon> pairWeaponClass);

	UFUNCTION(BlueprintCallable) void SpawnBaseWeaponCase(TSubclassOf<ACBP_WeaponCase> UsingWeaponClass);


	UFUNCTION(BlueprintCallable) void SerchOnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION(BlueprintCallable) void SerchOnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable) void SetHp_GaugeEnd();

protected:
	UPROPERTY(VisibleAnyWhere) class USphereComponent* targetSearchCollision;
	UPROPERTY(VisibleAnywhere) class UAIPerceptionComponent* AICharacterPerseption;

protected:
	UPROPERTY(VisibleAnywhere) class UWidgetComponent* Hp_Bar;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon") TSubclassOf<ACBP_WeaponCase> WeaponClass;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "AI") class UBehaviorTree* AI_BehaviorTree;
//	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "AI") UAnimMontage* BeginMontage;
	
	UFUNCTION() void AICharacterOnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION() void DestroyThisCharacter();


	ACBP_WeaponCase* weaponCase;

public:
	bool isSpawnAICharacter = false;
	FVector spawnLocalLocation;

	AActor* SpawnerActor = nullptr;
	AActor* SpawnerWeaponActor = nullptr;

private:
	float curDeadTime = 0;
	float DeleteTime = 5;
};
