// Fill out your copyright notice in the Description page of Project Settings.


#include "CBPN_NextAttack.h"
#include "Logger/Logger.h"
#include "Character/CBP_Character.h"

UCBPN_NextAttack::UCBPN_NextAttack()
{
	NotifyName = FName("NextAttack");
}

FString UCBPN_NextAttack::GetNotifyName_Implementation() const
{
	return NotifyName.ToString();
}

void UCBPN_NextAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (auto* character = Cast<ACBP_Character>(MeshComp->GetOwner()))
	{
		character->enable_Next_Attack = Enable;
	}
}