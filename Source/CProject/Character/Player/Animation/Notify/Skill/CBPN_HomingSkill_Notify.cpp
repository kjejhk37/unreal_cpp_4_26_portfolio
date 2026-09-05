// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/Animation/Notify/Skill/CBPN_HomingSkill_Notify.h"
#include "Character/CBP_Character.h"

#include "Macro/MathMacro.h"
#include "Macro/MyMacro.h"
#include "Macro/KismetMacro.h"
#include "Logger/Logger.h"

UCBPN_HomingSkill_Notify::UCBPN_HomingSkill_Notify()
{

}

FString UCBPN_HomingSkill_Notify::GetNotifyName_Implementation() const
{
	return FString("Homing_Skill_Notify_State");
}

void UCBPN_HomingSkill_Notify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);


	if (ACBP_Character* character = Cast<ACBP_Character>(MeshComp->GetOwner()))
	{
		ACBP_Skill* skill;

		// 이곳에서 Spawn하면 죽음 조심
		character->SkillSpawn(skillClass, skill);

		ACBP_Spawn_HomingSkill* HommingSkill = Cast<ACBP_Spawn_HomingSkill>(skill);
		if (HommingSkill == nullptr)
		{
			DestroyActor(skill);
			return;
		}

		HommingSkill->centerStartPos = CenterStartPos;
		HommingSkill->centerEndPos = CenterEndPos;

		HommingSkill->centerStartRotRoll = centerStartRotRoll;
		HommingSkill->localLookVector = localLookVector;

		HommingSkill->Trail_Start = Trail_Start;
		HommingSkill->Trail_End = Trail_End;

		HommingSkill->delayTime = DelayTime;
		HommingSkill->SetTargetTime = SetTargetTime;

		HommingSkill->moveSpeed = MoveSpeed;
	
		HommingSkill->homingType = homingType;

		HommingSkill->damage = damage;
		HommingSkill->attackType = attackType;
		skill->attackHitType = attackHitType;

		FVector PushVector = ActorLocalToWorldVector(character, pushVector);
		float lenght;
		PushVector.ToDirectionAndLength(PushVector, lenght);

		skill->pushVector = PushVector;

		HommingSkill->SetSpawn(nullptr);
		skills.Add(TTuple<AActor*, ACBP_Skill*>(character, skill));
	}
}

void UCBPN_HomingSkill_Notify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
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

void UCBPN_HomingSkill_Notify::NotifyTick(class USkeletalMeshComponent * MeshComp, class UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

}

