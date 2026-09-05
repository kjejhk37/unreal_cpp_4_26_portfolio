// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/Soldier/CBP_Soldier_Gun.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"

ACBP_Soldier_Gun::ACBP_Soldier_Gun()
{
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	GetCapsuleComponent()->SetCapsuleHalfHeight(90);

	InteractionCollision->SetCollisionProfileName(FName("NoCollision"));
}


void ACBP_Soldier_Gun::Action()
{

}

void ACBP_Soldier_Gun::EquipOrUnEquip()
{

}

void ACBP_Soldier_Gun::ActionDropping(bool& Success)
{

}

void ACBP_Soldier_Gun::SetDie()
{
	Super::SetDie();

	GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &ThisClass::SoldierOnMontageEnded);
}

void ACBP_Soldier_Gun::SoldierOnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (EndParticle != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EndParticle, GetActorLocation(),
			FRotator(0, 0, 0), FVector(1, 1, 1), true);
	}

	DestroyThisCharacter();
}