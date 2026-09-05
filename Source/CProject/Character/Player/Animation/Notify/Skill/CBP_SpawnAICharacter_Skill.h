// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Skill/Spawn_Skill/Spawn_Skel/CBP_SpawnSkelArmy_Skill.h"
#include "Struct/SCharacter.h"
#include "Character/AICharacter/CBP_AICharacter.h"

#include "CBP_SpawnAICharacter_Skill.generated.h"

UCLASS()
class CPROJECT_API UCBP_SpawnAICharacter_Skill : public UAnimNotifyState
{
	GENERATED_BODY()


public:
	UCBP_SpawnAICharacter_Skill();

	virtual FString GetNotifyName_Implementation() const override;
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;
	virtual void NotifyTick(class USkeletalMeshComponent * MeshComp, class UAnimSequenceBase * Animation, float FrameDeltaTime)override;

public:
	UPROPERTY(EditAnywhere, Category = "SkillClass") TSubclassOf<ACBP_SpawnSkelArmy_Skill> skillClass;
	UPROPERTY(EditAnywhere, Category = "AICharacterClass") TSubclassOf<ACBP_AICharacter> spawnCharacterClass;
	UPROPERTY(EditAnywhere, Category = "SpawnParticle") class UParticleSystem* SpawnParticle;

	UPROPERTY(EditAnywhere, Category = "Setting") FVector LocalStartPos;
	UPROPERTY(EditAnywhere, Category = "Setting") FVector LocalEndPos;
	UPROPERTY(EditAnywhere, Category = "Setting") float startRotatorYaw;

	UPROPERTY(EditAnywhere, Category = "Setting")  ESkillType skillType = ESkillType::Skill_1;

	UPROPERTY(EditAnywhere, Category = "Setting")  bool isSpawnLife = false;
	UPROPERTY(EditAnywhere, Category = "Setting")  float spawnTime = 5;


	TMap<AActor*, ACBP_Skill*> skills;
//	UPROPERTY() ACBP_Skill* skill;
	
};
