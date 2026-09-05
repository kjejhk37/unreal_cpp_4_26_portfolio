// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/ArcherSkel/CBP_ArcherSkel_AICharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include PairWeaponPath

#include "Macro/MyMacro.h"
#include "Logger/Logger.h"

ACBP_ArcherSkel_AICharacter::ACBP_ArcherSkel_AICharacter()
{
	GetMesh()->SetRelativeLocation(FVector(0, 0, -100));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	GetCapsuleComponent()->SetCapsuleHalfHeight(100);

	InteractionCollision->SetCollisionProfileName(FName("NoCollision"));

	CreateDefaultSubobjectAuto(Quiver);
	SetAttachRules(Rules);
	Quiver->SetupAttachment(GetMesh(), FName("Quiver"));
	Quiver->SetCollisionProfileName(FName("NoCollision"));
}

void ACBP_ArcherSkel_AICharacter::BeginPlay()
{
	Super::BeginPlay();

//	SpawnBaseWeapon(mainWeaponClass, pairWeaponClass);
}

void ACBP_ArcherSkel_AICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACBP_ArcherSkel_AICharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

// 안쓸꺼라서 일부로 비어놓음 -> 터지는 것을 방지하기 위함
void ACBP_ArcherSkel_AICharacter::Action()
{

}
void ACBP_ArcherSkel_AICharacter::EquipOrUnEquip()
{

}
