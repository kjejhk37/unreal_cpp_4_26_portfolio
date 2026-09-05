// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/ArcherSkel/Notify/CBPN_ArcherSkel_ShotArrow.h"
#include "Character/CBP_Character.h"

#include "Macro/MyMacro.h"

#include "Logger/Logger.h"

UCBPN_ArcherSkel_ShotArrow::UCBPN_ArcherSkel_ShotArrow()
{

}

FString UCBPN_ArcherSkel_ShotArrow::GetNotifyName_Implementation() const
{
	return FString("ArcherSkel_ShotArrow");
}

void UCBPN_ArcherSkel_ShotArrow::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	curTime = 0;

	if (arrowClass == nullptr) return;

	ACBP_Skill* skill;

	ACBP_Character* character = Cast<ACBP_Character>(MeshComp->GetOwner());
	if (character == nullptr) return;

	character->SkillSpawn(arrowClass, skill);
	if (skill == nullptr) return;

	ACBP_ArrowShot* arrowSkill = Cast<ACBP_ArrowShot>(skill);
	if (arrowSkill == nullptr) return;


	arrowSkill->shotReadySocket = shotReadySocket;
	arrowSkill->shotSocket = shotSocket;
	arrowSkill->trail_Start = trail_Start;
	arrowSkill->trail_End = trail_End;
	skill->SetSpawn(nullptr);

	skills.Add(TTuple<AActor*, ACBP_Skill*>(character, skill));
}

void UCBPN_ArcherSkel_ShotArrow::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	ACBP_Skill* skill = skills[MeshComp->GetOwner()];

	if (skill == nullptr) return;

	ACBP_ArrowShot* arrowSkill = Cast<ACBP_ArrowShot>(skill);
	if (arrowSkill == nullptr) return;

//	bool inSuccess = true;
//	bool outSuccess = false;
//	arrowSkill->Play(inSuccess, outSuccess);

	if (curTime > SetTime)
	{
		bool inSuccess = true;
		bool outSuccess = false;
		arrowSkill->Play(inSuccess, outSuccess);
	}
	else
	{
		DestroyActor(skill);
	}

	skills.Remove(MeshComp->GetOwner());
}

void UCBPN_ArcherSkel_ShotArrow::NotifyTick(class USkeletalMeshComponent * MeshComp, class UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	curTime += FrameDeltaTime;
}
