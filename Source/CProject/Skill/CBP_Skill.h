// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Interface/CBPI_Skill.h"
#include "Interface/CBPI_CanGetAttackDataObject.h"

#include "Enums/EWeapon.h"
#include "Struct/SCharacter.h"

#include "CBP_Skill.generated.h"

UCLASS()
class CPROJECT_API ACBP_Skill : public AActor, public ICBPI_Skill , public ICBPI_CanGetAttackDataObject
{
	GENERATED_BODY()
	
public:	
	ACBP_Skill();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	void Play(bool const InSuccess, bool& Success)override;
	void SetSpawn(AActor* centerActor)override;

	void SetStart()override;
	void SetEnd() override;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly, Category = "Type") ESkillType skillType;
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly, Category = "Type") EAttackType attackType;
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly, Category = "Type") EAttackHitType attackHitType;
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly, Category = "Type") EGuardSerchType guardSerchType;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Set") FVector centerStartPos;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Set") FVector centerEndPos;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Set") float centerStartRoll = 0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Set") FVector pushVector;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Set") F_Hp_Update_Value damage;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Set") EAttackPushType attackPushType = EAttackPushType::PushVector;

	void SpawnTextActor(FString string, FVector Location, FVector fontColor = FVector(1,1,1),float fontSize = 24, float outlineFontSize = 1);
	void SpawnAttackParticle(class UParticleSystem* inAttackParticle, TSubclassOf<class ACBP_Particle> inAttackParticleActorClass, FVector particleLocation);

protected:
	UPROPERTY(VisibleAnywhere) class USceneComponent* center;

	UPROPERTY(BlueprintReadOnly, Category = "Trasnform") FVector worldStartPosition = FVector(1000, 1000, -50000);
	UPROPERTY(BlueprintReadOnly, Category = "Trasnform") FVector worldEndPosition = FVector(1000,1000,-50000);

	UPROPERTY(BlueprintReadWrite, Category = "Trasnform") FRotator startRotation;
	UPROPERTY(BlueprintReadOnly, Category = "Trasnform") AActor* Target;


public:
	void GetInstigatorcharacter(ACBP_Character*& outCharacter)override;
	void GetFinalDamage(F_Hp_Update_Value& outDamage) override;

	void GetAttackType(EAttackType& outAttackType) override;
	void GetAttackHitType(EAttackHitType& outAttackHitType) override;

	void GetPushVector(FVector& outPushVector) override;
	void GetAttackPushType(EAttackPushType& outAttackPushType) override;

	void GetGuardSerchType(EGuardSerchType& outGuardSerchType) override;

	void GetCamp(ECamp& outCamp) override;
};
