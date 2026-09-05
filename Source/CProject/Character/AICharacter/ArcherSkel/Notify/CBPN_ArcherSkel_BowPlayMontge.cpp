// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/ArcherSkel/Notify/CBPN_ArcherSkel_BowPlayMontge.h"
#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/Main_Weapon/BowType/CBP_BowMainWeapon.h"
#include "Character/CBP_Character.h"
#include "Logger/Logger.h"

UCBPN_ArcherSkel_BowPlayMontge::UCBPN_ArcherSkel_BowPlayMontge()
{
	NotifyName = FName("ArcherSkel_BowPlayMontge");
}

FString UCBPN_ArcherSkel_BowPlayMontge::GetNotifyName_Implementation() const
{
	return NotifyName.ToString();
}

void UCBPN_ArcherSkel_BowPlayMontge::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACBP_Character* character = Cast<ACBP_Character>(MeshComp->GetOwner());
	if (character == nullptr) return;

	ACBP_BowMainWeapon* bowWeapon = Cast<ACBP_BowMainWeapon>(character->main_Weapon);
	if (bowWeapon == nullptr) return;

	bowWeapon->PlayMontageCharging();

}
