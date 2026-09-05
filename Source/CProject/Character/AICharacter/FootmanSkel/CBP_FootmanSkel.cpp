// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/FootmanSkel/CBP_FootmanSkel.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"

#include "Macro/MyMacro.h"
#include "Logger/Logger.h"

ACBP_FootmanSkel::ACBP_FootmanSkel()
{
	GetMesh()->SetRelativeLocation(FVector(0, 0, -100));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	GetCapsuleComponent()->SetCapsuleHalfHeight(100);

	InteractionCollision->SetCollisionProfileName(FName("NoCollision"));
}

void ACBP_FootmanSkel::BeginPlay()
{
	Super::BeginPlay();

	SpawnBaseWeapon(mainWeaponClass, pairWeaponClass);
}

void ACBP_FootmanSkel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACBP_FootmanSkel::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

// 안쓸꺼라서 일부로 비어놓음 -> 터지는 것을 방지하기 위함
void ACBP_FootmanSkel::Action()
{

}
void ACBP_FootmanSkel::EquipOrUnEquip()
{

}
