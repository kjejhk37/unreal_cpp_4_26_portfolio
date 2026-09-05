// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/Animation/Notify/Skill/CBP_SpawnAICharacter_Skill.h"
#include "Character/CBP_Character.h"

#include "Macro/MyMacro.h"
#include "Logger/Logger.h"

UCBP_SpawnAICharacter_Skill::UCBP_SpawnAICharacter_Skill()
{
	// Notify 종류별로 나누기 (셋팅해야할 변수별로 나누어야 할듯)
}

FString UCBP_SpawnAICharacter_Skill::GetNotifyName_Implementation() const
{
	return FString("Spawn_Skill_Notify_State");
}

void UCBP_SpawnAICharacter_Skill::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);



	if (ACBP_Character* character = Cast<ACBP_Character>(MeshComp->GetOwner()))
	{
		ACBP_Skill* skill;

		// 이곳에서 Spawn하면 죽음 조심
		character->SkillSpawn(skillClass, skill);
		skill->centerStartPos = LocalStartPos;
		skill->centerEndPos = LocalEndPos;

		skill->skillType = skillType;

		if (ACBP_SpawnSkelArmy_Skill* spawnSkill = Cast<ACBP_SpawnSkelArmy_Skill>(skill))
		{
			spawnSkill->spawnCharacterClass = spawnCharacterClass;
			spawnSkill->startRotatorYaw = startRotatorYaw;
			spawnSkill->SpawnParticle = SpawnParticle;

			spawnSkill->isSpawnLife = isSpawnLife;
			spawnSkill->spawnTime = spawnTime;
		}

		skill->SetSpawn(nullptr);
		skills.Add(TTuple<AActor*, ACBP_Skill*>(character, skill));
	}

}

void UCBP_SpawnAICharacter_Skill::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	ACBP_Skill* skill = nullptr;

	if (skills.Contains(MeshComp->GetOwner()) == true)
	{
		skill = skills[MeshComp->GetOwner()];

		if (ACBP_Character* character = Cast<ACBP_Character>(MeshComp->GetOwner()))
		{
			bool inSuccsee = true;
			bool outSuccess = false;
			skill->Play(inSuccsee, outSuccess);
		}

		skills.Remove(MeshComp->GetOwner());
	}
}

void UCBP_SpawnAICharacter_Skill::NotifyTick(class USkeletalMeshComponent * MeshComp, class UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

}

