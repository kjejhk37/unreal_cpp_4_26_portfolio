// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/Animation/Notify/Skill/CBPN_AnimationSkill_Notify.h"
#include "Character/CBP_Character.h"

#include "Macro/MyMacro.h"
#include "Macro/MathMacro.h"
#include "Macro/KismetMacro.h"
#include "Logger/Logger.h"

UCBPN_AnimationSkill_Notify::UCBPN_AnimationSkill_Notify()
{
	// Notify 종류별로 나누기 (셋팅해야할 변수별로 나누어야 할듯)
}

FString UCBPN_AnimationSkill_Notify::GetNotifyName_Implementation() const
{
	return FString("Animation_Skill_Notify_State");
}

void UCBPN_AnimationSkill_Notify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (ACBP_Character* character = Cast<ACBP_Character>(MeshComp->GetOwner()))
	{
		ACBP_Skill* skill;


		// 이곳에서 Spawn하면 죽음 조심
		character->SkillSpawn(skillClass, skill);
		ACBP_AnimationType_SkillType* AnimationSkill = Cast<ACBP_AnimationType_SkillType>(skill);
		if (AnimationSkill == nullptr)
		{
			DestroyActor(skill);
			return;
		}

		AnimationSkill->centerStartPos = centerStartPos;
		AnimationSkill->centerEndPos = centerEndPos;

		AnimationSkill->meshStartRelativeLocation = MeshStartRelativeLocation;
		AnimationSkill->meshStartRot = MeshStartRot;
		AnimationSkill->meshStartScale = MeshStartScale;

		AnimationSkill->centerStartLookVector = CenterStartLookVector;
		AnimationSkill->centerStartRoll = CenterStartRoll;
		AnimationSkill->centerEndRotator = CenterEndRotator;

		AnimationSkill->centerStartScale = CenterStartScale;
		AnimationSkill->centerEndScale = CenterEndScale;

		AnimationSkill->animationTime = AnimationTime;
		AnimationSkill->delayTime = DelayTime;
		AnimationSkill->destroyTime = DestroyTime;

		AnimationSkill->Trail_Start = Trail_Start;
		AnimationSkill->Trail_End = Trail_End;

		AnimationSkill->AttackNumber = AttackNumber;

		AnimationSkill->damage = damage;
		skill->attackType = attackType;
		skill->attackHitType = attackHitType;

		FVector PushVector = ActorLocalToWorldVector(character, pushVector);
		float lenght;
		PushVector.ToDirectionAndLength(PushVector, lenght);

		skill->pushVector = PushVector;

		AnimationSkill->SetSpawn(nullptr);
		skills.Add(TTuple<AActor*, ACBP_Skill*>(character, skill));
	}

}

void UCBPN_AnimationSkill_Notify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
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

void UCBPN_AnimationSkill_Notify::NotifyTick(class USkeletalMeshComponent * MeshComp, class UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

}

