// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/Animation/Notify/Skill/CBPN_ProjectileSkillNotify.h"
#include "Character/CBP_Character.h"

#include "Macro/MathMacro.h"
#include "Macro/MyMacro.h"
#include "Macro/KismetMacro.h"
#include "Logger/Logger.h"

UCBPN_ProjectileSkillNotify::UCBPN_ProjectileSkillNotify()
{
	// Notify 종류별로 나누기 (셋팅해야할 변수별로 나누어야 할듯)
}

FString UCBPN_ProjectileSkillNotify::GetNotifyName_Implementation() const
{
	return FString("Skill_Projectile_Notify_State");
}

void UCBPN_ProjectileSkillNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (ACBP_Character* character = Cast<ACBP_Character>(MeshComp->GetOwner()))
	{
		ACBP_Skill* skill;

		// 이곳에서 Spawn하면 죽음 조심
		character->SkillSpawn(skillClass, skill);

		ACBP_Projectile_Skill* projectileSkill = Cast<ACBP_Projectile_Skill>(skill);
		if (projectileSkill == nullptr)
		{
			DestroyActor(skill);
			return;
		}

		projectileSkill->centerStartPos = LocalStartPos;
		projectileSkill->centerEndPos = LocalEndPos;

		projectileSkill->delayTimes = DelayTimes;
		projectileSkill->localPointers = LocalPointers;
		projectileSkill->meshTypes = MeshTypes;
		
		projectileSkill->damage = damage;
		projectileSkill->attackType = attackType;
		skill->attackHitType = attackHitType;

		FVector PushVector = ActorLocalToWorldVector(character, pushVector);
		float lenght;
		PushVector.ToDirectionAndLength(PushVector, lenght);

		skill->pushVector = PushVector;

		projectileSkill->SetSpawn(nullptr);
		skills.Add(TTuple<AActor*, ACBP_Skill*>(character, skill));
	}

}

void UCBPN_ProjectileSkillNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (ACBP_Character* character = Cast<ACBP_Character>(MeshComp->GetOwner()))
	{
		ACBP_Skill* skill = skills[MeshComp->GetOwner()];

		if (skill == nullptr) return;

		bool inSuccsee = true;
		bool outSuccess = false;
		skill->Play(inSuccsee, outSuccess);

		skills.Remove(MeshComp->GetOwner());
	}
}

void UCBPN_ProjectileSkillNotify::NotifyTick(class USkeletalMeshComponent * MeshComp, class UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

}

