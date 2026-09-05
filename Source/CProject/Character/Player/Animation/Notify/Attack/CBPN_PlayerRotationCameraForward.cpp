// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/Animation/Notify/Attack/CBPN_PlayerRotationCameraForward.h"
#include "Character/Player/CBP_Player.h"
#include "Logger/Logger.h"

UCBPN_PlayerRotationCameraForward::UCBPN_PlayerRotationCameraForward()
{
	NotifyName = FName("PlayerRotation_CameraForward");
}

FString UCBPN_PlayerRotationCameraForward::GetNotifyName_Implementation() const
{
	return NotifyName.ToString();
}

void UCBPN_PlayerRotationCameraForward::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACBP_Character* character = Cast<ACBP_Character>(MeshComp->GetOwner());
	if (character == nullptr) return;

	FRotator newRotator = character->GetControlRotation();
	character->SetActorRotation(FRotator(0, newRotator.Yaw, 0));

}
