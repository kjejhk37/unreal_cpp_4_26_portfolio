// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/Main_Weapon/GunType/CBP_GunType_MainWeapon.h"

#include "Character/CBP_Character.h"
#include "Character/Player/CBP_PlayerController.h"

#include "Macro/KismetMacro.h"
#include "Macro/MyMacro.h"

#include "Logger/Logger.h"

ACBP_GunType_MainWeapon::ACBP_GunType_MainWeapon()
{

}

void ACBP_GunType_MainWeapon::BeginPlay()
{
	Super::BeginPlay();

	SetGunInfo();

	ShotMontageTemp = ShotMontage;

}

void ACBP_GunType_MainWeapon::Shot(int ShotNum, UAnimMontage* shotMontage)
{
	if (shotMontage != nullptr)
	{
		ShotMontage = shotMontage;
	}
	else
	{
		ShotMontage = ShotMontageTemp;
	}

	bool canShot = false;
	CanShot(canShot, ShotNum);

	if (canShot == false)
	{
		if (ACBP_Character* character = Cast<ACBP_Character>(GetInstigator()))
		{
			character->GunReLoad();
		}

		return;
	}

	bool success = false;
	DecreasingBullet(success, ShotNum);
	if (success == false) return;

	skeletalMesh->GetAnimInstance()->Montage_Play(ShotMontage);
}

void ACBP_GunType_MainWeapon::ShotTrace(bool const InSuccess, bool & Success, FHitResult & OutHit, bool & IsHit)
{
	// 조준을 위한 것 기본적인 위치는 AimOffSet을 이용하지만 쏘는 순간에는 해당 값을 통해서 계산

	FVector start;
	FVector end;

	switch (meshType)
	{
	case EMeshType::StaticMesh:
		start = staticMesh->GetSocketLocation(ShotSocket);
		end = start + staticMesh->GetRightVector() * AttackLength;
		break;
	case EMeshType::SkeletalMesh:
		start = skeletalMesh->GetSocketLocation(ShotSocket);
		end = start + skeletalMesh->GetRightVector() * AttackLength;
		break;
	}

	UKismetSystemLibrary::LineTraceSingle(
		GetWorld(),
		start,
		end,
		ETraceTypeQuery::TraceTypeQuery3,
		false,
		{ GetInstigator() },
		EDrawDebugTrace::Type::Persistent,
		OutHit,
		true
	);

	OutHit.bBlockingHit = IsHit;
	Success = true;
}

void ACBP_GunType_MainWeapon::ReLoad(bool & Success)
{
	RemainBullet = MaxBullet;
	Success = true;

	ACBP_Character* character = Cast<ACBP_Character>(GetInstigator());
	if (character == nullptr) return;

	ACBP_PlayerController* playerController = Cast<ACBP_PlayerController>(character->GetController());
	if (playerController == nullptr) return;

	playerController->Player_RemainBullet_Interface(MaxBullet, RemainBullet);
}

void ACBP_GunType_MainWeapon::CanShot(bool& canShot, int Num)
{
	canShot = (RemainBullet >= Num);
}

void ACBP_GunType_MainWeapon::DecreasingBullet(bool& Success, int Num)
{
	Success = false;
	if (RemainBullet < Num) return;

	Success = true;
	RemainBullet -= Num;

	ACBP_Character* character = Cast<ACBP_Character>(GetInstigator());
	if (character == nullptr) return;

	ACBP_PlayerController* playerController = Cast<ACBP_PlayerController>(character->GetController());
	if (playerController == nullptr) return;

	playerController->Player_RemainBullet_Interface(MaxBullet, RemainBullet);
}

void ACBP_GunType_MainWeapon::SpawnFaiingBullet()
{
	ACBP_Non_InteractionObject* bullet;

	FActorSpawnParameters param;

	SpawnActorUseClass(bullet, FallingBullet, param);

	FVector velocity = -skeletalMesh->GetForwardVector();
	float power;

	velocity.Y += (float)(rand() % 10 - 5) / 10.0f;
	velocity.Z += (float)(rand() % 10 - 5) / 10.0f;

	velocity.ToDirectionAndLength(velocity, power);
	power = 500;

	bullet->SetActorLocation(skeletalMesh->GetSocketLocation(BulletSocket));
	bullet->SetImpulse(false, power, velocity, bullet->GetActorLocation());

}

void ACBP_GunType_MainWeapon::SpawnFaiingMagazine()
{
	ACBP_Non_InteractionObject* magazine;

	FActorSpawnParameters param;
	SpawnActorUseClass(magazine, FallingMagazine, param);

	magazine->SetActorLocation(skeletalMesh->GetSocketLocation(MagazineSocket));
}

void ACBP_GunType_MainWeapon::Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType)
{
	Super::Set_NonSimul_ComponentsBase(newMeshType, newInteractionType);
}

void ACBP_GunType_MainWeapon::SetGunInfo()
{
	if (GunInfoDataAsset == nullptr) return;

	F_GunTypeInfo gunInfo;
	GunInfoDataAsset->GetGunInfo(weaponName, gunInfo);

	AttackLength = gunInfo.AttackLength;

	FallingBullet = gunInfo.FallingBullet;
	FallingMagazine = gunInfo.FallingMagazine;

	MagazineSocket = gunInfo.MagazineSocket;
	BulletSocket = gunInfo.BulletSocket;
	ShotSocket = gunInfo.ShotSocket;

	RemainBullet = gunInfo.RemainBullet;
	MaxBullet = gunInfo.MaxBullet;
}

void ACBP_GunType_MainWeapon::UpdateInterface(bool Equip)
{
	ACBP_Character* character = Cast<ACBP_Character>(GetInstigator());
	if (character == nullptr) return;

	ACBP_PlayerController* playerController = Cast<ACBP_PlayerController>(character->GetController());
	if (playerController == nullptr) return;

	playerController->Player_RemainBullet_Interface_newVisible(Equip);

	if (Equip == false) return;
	playerController->Player_RemainBullet_Interface(MaxBullet, RemainBullet);
}