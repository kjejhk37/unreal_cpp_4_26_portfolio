// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/Animation/Notify/Skill/PalatosSkill/CBPN_PalatosSkill_Notify.h"
#include "Character/CBP_Character.h"

#include "Macro/MathMacro.h"
#include "Macro/MyMacro.h"
#include "Macro/KismetMacro.h"

#include "Logger/Logger.h"

UCBPN_PalatosSkill_Notify::UCBPN_PalatosSkill_Notify()
{

}

FString UCBPN_PalatosSkill_Notify::GetNotifyName_Implementation() const
{
	return FString("PalatosSkill");
}

void UCBPN_PalatosSkill_Notify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);


	if (ACBP_Character* character = Cast<ACBP_Character>(MeshComp->GetOwner()))
	{
		// 이곳에서 Spawn하면 죽음 조심
		character->SkillSpawn(skillClass, skill);

		ACBP_Palatos_Skill* palatosSkill = Cast<ACBP_Palatos_Skill>(skill);
		if (palatosSkill == nullptr)
		{
			DestroyActor(skill);
			return;
		}

		palatosSkill->centerStartPos = LocalStartPos;
		palatosSkill->centerEndPos = LocalEndPos;

		palatosSkill->DelayTime = DelayTime;
		palatosSkill->MoveSpeed = MoveSpeed;

		palatosSkill->damage = damage;
		palatosSkill->attackType = attackType;
		palatosSkill->attackHitType = attackHitType;

		palatosSkill->PalatosNum = PalatosNum;
		palatosSkill->PalatosLenght = PalatosLenght;

		palatosSkill->attackSkillClass = attackSkillClass;
		palatosSkill->SetEndMontage = SetEndMontage;

		palatosSkill->skillType = skillType;

		palatosSkill->isChargeType = isChargeType;

		FVector PushVector = ActorLocalToWorldVector(character, pushVector);
		float lenght;
		PushVector.ToDirectionAndLength(PushVector, lenght);

		skill->pushVector = PushVector;

		palatosSkill->SetSpawn(nullptr);
	}
}

void UCBPN_PalatosSkill_Notify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (ACBP_Character* character = Cast<ACBP_Character>(MeshComp->GetOwner()))
	{
		if (skill == nullptr) return;

		bool inSuccsee = true;
		bool outSuccess = false;
		skill->Play(inSuccsee, outSuccess);
	}

}

void UCBPN_PalatosSkill_Notify::NotifyTick(class USkeletalMeshComponent * MeshComp, class UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

}