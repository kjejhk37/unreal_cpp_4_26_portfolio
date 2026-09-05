// Fill out your copyright notice in the Description page of Project Settings.


#include "CBPN_Trail_Particle_Activate.h"
#include "Logger/Logger.h"
#include "Character/CBP_Character.h"
#include "Interface/CBPI_Trail_Particle_Weapon.h"

UCBPN_Trail_Particle_Activate::UCBPN_Trail_Particle_Activate()
{
	NotifyName = FName("Particle_Activate Or DeActivate");
}

FString UCBPN_Trail_Particle_Activate::GetNotifyName_Implementation() const
{
	return NotifyName.ToString();
}

void UCBPN_Trail_Particle_Activate::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACBP_Character* character = Cast<ACBP_Character>(MeshComp->GetOwner());
	if (character == nullptr) return;

	if (ICBPI_Trail_Particle_Weapon* weapon = Cast<ICBPI_Trail_Particle_Weapon>(character->main_Weapon))
	{
		(isActivate) ? weapon->TrailParticleActivate() : weapon->TrailParticleDeActivate();
	}

	if (ICBPI_Trail_Particle_Weapon* weapon = Cast<ICBPI_Trail_Particle_Weapon>(character->pair_Weapon))
	{
		(isActivate) ? weapon->TrailParticleActivate() : weapon->TrailParticleDeActivate();
	}

}