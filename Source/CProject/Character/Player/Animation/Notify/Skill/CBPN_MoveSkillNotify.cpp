// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/Animation/Notify/Skill/CBPN_MoveSkillNotify.h"
#include "Character/CBP_Character.h"

#include "Macro/MathMacro.h"
#include "Macro/MyMacro.h"
#include "Macro/KismetMacro.h"
#include "Logger/Logger.h"

UCBPN_MoveSkillNotify::UCBPN_MoveSkillNotify()
{
	// Notify 종류별로 나누기 (셋팅해야할 변수별로 나누어야 할듯)
}

FString UCBPN_MoveSkillNotify::GetNotifyName_Implementation() const
{
	return FString("Move_Skill_Notify_State");
}

void UCBPN_MoveSkillNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
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

		if (ACBP_MoveSkill* moveSkill = Cast<ACBP_MoveSkill>(skill))
		{
			moveSkill->DelayTime = DelayTime;
			moveSkill->PlayTime = PlayTime;

			moveSkill->upPos = upPos;
			moveSkill->underPos = underPos;
		}


		skill->damage = damage;
		skill->attackType = attackType;
		skill->attackHitType = attackHitType;

		FVector PushVector = ActorLocalToWorldVector(character, pushVector);
		float lenght;
		PushVector.ToDirectionAndLength(PushVector, lenght);

		skill->pushVector = PushVector;

		skill->SetSpawn(nullptr);
		skills.Add(TTuple<AActor*, ACBP_Skill*>(character, skill));
	}

}

void UCBPN_MoveSkillNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (ACBP_Character* character = Cast<ACBP_Character>(MeshComp->GetOwner()))
	{
		ACBP_Skill* skill = skills[MeshComp->GetOwner()];

		bool inSuccsee = true;
		bool outSuccess = false;
		skill->Play(inSuccsee, outSuccess);

		skills.Remove(MeshComp->GetOwner());
	}
}

void UCBPN_MoveSkillNotify::NotifyTick(class USkeletalMeshComponent * MeshComp, class UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

}

