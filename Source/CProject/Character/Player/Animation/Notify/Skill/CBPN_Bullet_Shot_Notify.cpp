// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/Animation/Notify/Skill/CBPN_Bullet_Shot_Notify.h"
#include "Character/CBP_Character.h"

#include "Logger/Logger.h"

UCBPN_Bullet_Shot_Notify::UCBPN_Bullet_Shot_Notify()
{
	NotifyName = FName("BulletShot");
}

FString UCBPN_Bullet_Shot_Notify::GetNotifyName_Implementation() const
{
	return NotifyName.ToString();
}

void UCBPN_Bullet_Shot_Notify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);


	if (ShotClass == nullptr) return;

	ACBP_Character* character = Cast<ACBP_Character>(MeshComp->GetOwner()->GetInstigator());
	if (character == nullptr) return;
//	ACBP_Character* character = Cast<ACBP_Character>(MeshComp->GetOwner());
//	if (character == nullptr)
//	{
//		character = Cast<ACBP_Character>(MeshComp->GetOwner()->GetInstigator());
//		if (character == nullptr) return;
//	}

	character->SkillSpawn(ShotClass, skill);
	if (skill == nullptr) return;

	ACBP_BulletType_Skill* bulletSkill = Cast<ACBP_BulletType_Skill>(skill);
	if (bulletSkill == nullptr) return;

	skill->SetOwner(MeshComp->GetOwner());

	bulletSkill->shotSocket = shotSocket;
	bulletSkill->SetSpawn(nullptr);

	bool inSuccess = true;
	bool outSuccess = false;
	bulletSkill->Play(inSuccess, outSuccess);
}
