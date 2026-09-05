// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/CBP_Skill.h"
#include "Particle/CBP_Particle.h"
#include "CBP_SimpleAttackSkill.generated.h"


UCLASS()
class CPROJECT_API ACBP_SimpleAttackSkill : public ACBP_Skill
{
	GENERATED_BODY()
	

public:
	ACBP_SimpleAttackSkill();
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void Play(bool const InSuccess, bool& Success)override;
	void SetSpawn(AActor* centerActor)override;

	UFUNCTION() void SetStart() override;
	UFUNCTION() void SetEnd() override;

	virtual void CorrectComponentSerch(bool& canAttack,AActor* OtherActor) PURE_VIRTUAL(ACBP_SimpleAttackSkill::CorrectComponentSerch, return;);

public:
	UPROPERTY(EditDefaultsOnly, Category = "Set") float playDelayTime = 0;
	UPROPERTY(EditDefaultsOnly, Category = "Set") float playTime = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Set") float StartScale = 1;
	UPROPERTY(EditDefaultsOnly, Category = "Set") float EndScale = 5;


protected:
	UPROPERTY(VisibleAnywhere) class USphereComponent* AttackComponent;
	UPROPERTY(VisibleAnywhere) class UParticleSystemComponent* particle;

	UFUNCTION() void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION() void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditDefaultsOnly) class UParticleSystem* attackParticle;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<ACBP_Particle> attackParticleActorClass;

private:
	TArray<AActor*> AttackActors;

	float curTime = 0;
	bool isPlay = false;
};
