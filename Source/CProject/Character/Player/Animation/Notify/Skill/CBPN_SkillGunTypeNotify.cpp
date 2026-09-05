// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/Animation/Notify/Skill/CBPN_SkillGunTypeNotify.h"
#include "Character/CBP_Character.h"

#include "Macro/MathMacro.h"
#include "Macro/MyMacro.h"
#include "Macro/KismetMacro.h"
#include "Logger/Logger.h"

UCBPN_SkillGunTypeNotify::UCBPN_SkillGunTypeNotify()
{

}

FString UCBPN_SkillGunTypeNotify::GetNotifyName_Implementation() const
{
	return FString("Skill_Spawn_Gun_Notify_State");
}

void UCBPN_SkillGunTypeNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (ACBP_Character* character = Cast<ACBP_Character>(MeshComp->GetOwner()))
	{
		ACBP_Skill* skill;

		// 이곳에서 Spawn하면 죽음 조심
		character->SkillSpawn(skillClass, skill);

		ACBP_Spawn_Gun_Skill* gunSkill = Cast<ACBP_Spawn_Gun_Skill>(skill);
		if (gunSkill == nullptr)
		{
			DestroyActor(skill);
			return;
		}

		gunSkill->centerStartPos = LocalStartPos;
		gunSkill->centerEndPos = LocalEndPos;

		gunSkill->delayTime = DelayTime;
		gunSkill->attackCount = AttackCount;
		gunSkill->attackCoolTime = AttackCoolTime;
		gunSkill->attackLength = AttackLenght;
		gunSkill->endPlaySpeed = EndPlaySpeed;

		gunSkill->damage = damage;
		gunSkill->attackType = attackType;
		skill->attackHitType = attackHitType;

		skill->pushVector = FVector(0,0,0);

		gunSkill->SetSpawn(nullptr);
		skills.Add(TTuple<AActor*, ACBP_Skill*>(character, skill));
	}
}

void UCBPN_SkillGunTypeNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
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

void UCBPN_SkillGunTypeNotify::NotifyTick(class USkeletalMeshComponent * MeshComp, class UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

}
