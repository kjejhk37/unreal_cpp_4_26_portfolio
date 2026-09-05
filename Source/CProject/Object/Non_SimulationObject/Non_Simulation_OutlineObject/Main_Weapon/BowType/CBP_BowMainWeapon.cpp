// Fill out your copyright notice in the Description page of Project Settings.


#include "CBP_BowMainWeapon.h"


ACBP_BowMainWeapon::ACBP_BowMainWeapon()
{
	Set_NonSimul_ComponentsBase(EMeshType::SkeletalMesh, ECollisionType::None);

	weaponName = EWeaponName::Bow;
}

void ACBP_BowMainWeapon::PlayMontageCharging()
{
//	skeletalMesh->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &ThisClass::BowOnMontageEnded);
	skeletalMesh->GetAnimInstance()->Montage_Play(ChargingMontage, 1.0f);

}
void ACBP_BowMainWeapon::PlayMontageShoting()
{
	skeletalMesh->GetAnimInstance()->OnMontageEnded.Clear();
	skeletalMesh->GetAnimInstance()->Montage_Play(ShotingMontage, 1.0f);
}

void ACBP_BowMainWeapon::BeginPlay()
{
	Super::BeginPlay();

	skeletalOutlineMesh->SetRelativeLocation(FVector(-8.441f, 4.1519f, 0));
}

void ACBP_BowMainWeapon::BowOnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	PlayMontageShoting();
}

/*

void ACBP_BowMainWeapon::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}

void ACBP_BowMainWeapon::Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType)
{
	Super::Set_NonSimul_ComponentsBase(newMeshType, newInteractionType);

}


void ACBP_BowMainWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACBP_BowMainWeapon::Activate(bool InSuccess, bool& OutSuccess)
{
	Super::Activate(InSuccess, OutSuccess);
}

void ACBP_BowMainWeapon::DeActivate(bool InSuccess, bool& OutSuccess)
{
	Super::DeActivate(InSuccess, OutSuccess);
}


void ACBP_BowMainWeapon::SpawnArrow(bool& OutSuccess, AActor*& spawnArrowActor)
{
	// 스킬형태로 바꿔서 지금은 안쓸꺼임
}

void ACBP_BowMainWeapon::Shot(bool InSuccess, bool& OutSuccess)
{
	// 스킬형태로 바꿔서 지금은 안쓸꺼임
}

*/