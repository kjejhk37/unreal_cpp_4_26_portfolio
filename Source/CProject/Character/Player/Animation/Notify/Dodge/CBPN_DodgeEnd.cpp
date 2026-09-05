// Fill out your copyright notice in the Description page of Project Settings.


#include "CBPN_DodgeEnd.h"
#include "Character/Player/CBP_Player.h"
#include "Macro/MathMacro.h"

UCBPN_DodgeEnd::UCBPN_DodgeEnd()
{
	NotifyName = FName("DodgeEnd");
}

FString UCBPN_DodgeEnd::GetNotifyName_Implementation() const
{
	return NotifyName.ToString();
}

void UCBPN_DodgeEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (ACBP_Player* player = Cast<ACBP_Player>(MeshComp->GetOwner()))
	{
		player->GetMesh()->SetRelativeRotation(RotatorXYZ(0, 0, -90));
	}
}