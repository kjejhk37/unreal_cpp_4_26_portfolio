// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/Animation/Notify/Skill/CBPN_Player_ArrowShot.h"


#include "Character/CBP_Character.h"

#include "Logger/Logger.h"


UCBPN_Player_ArrowShot::UCBPN_Player_ArrowShot()
{
	NotifyName = FName("Player_ShotArrow");
}

FString UCBPN_Player_ArrowShot::GetNotifyName_Implementation() const
{
	return NotifyName.ToString();

}

void UCBPN_Player_ArrowShot::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (arrowClass == nullptr) return;

	ACBP_Character* character = Cast<ACBP_Character>(MeshComp->GetOwner());
	if (character == nullptr) return;

	character->SkillSpawn(arrowClass, skill);
	if (skill == nullptr) return;

	ACBP_Player_ArrowShot* arrowSkill = Cast<ACBP_Player_ArrowShot>(skill);
	if (arrowSkill == nullptr) return;


	arrowSkill->shotReadySocket = shotReadySocket;
	arrowSkill->shotSocket = shotSocket;
	arrowSkill->trail_Start = trail_Start;
	arrowSkill->trail_End = trail_End;
	skill->SetSpawn(nullptr);

	bool inSuccess = true;
	bool outSuccess = false;
	arrowSkill->Play(inSuccess, outSuccess);
}
