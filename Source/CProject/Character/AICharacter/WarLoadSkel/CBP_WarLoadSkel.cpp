// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/WarLoadSkel/CBP_WarLoadSkel.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"

#include "Macro/MyMacro.h"
#include "Logger/Logger.h"

ACBP_WarLoadSkel::ACBP_WarLoadSkel()
{
	GetMesh()->SetRelativeLocation(FVector(0, 0, -100));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	GetCapsuleComponent()->SetCapsuleHalfHeight(100);

	InteractionCollision->SetCollisionProfileName(FName("NoCollision"));
}

void ACBP_WarLoadSkel::BeginPlay()
{
	Super::BeginPlay();

	SpawnBaseWeapon(mainWeaponClass, pairWeaponClass);
}

void ACBP_WarLoadSkel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ghostTrailClass == nullptr) return;

	if (GetVelocity().Size() < 20) return;
	if (characterState == ECharacterState::Skill) return;

	curTime += DeltaTime;

	if (curTime > trailInterval)
	{
		curTime = 0;

		ACBP_GhostTrail* trail;
		
		FActorSpawnParameters param;
		SpawnActorUseClass(trail, ghostTrailClass, param);

		trail->trailTime = trailTime;
		trail->PoseCharacter = this;

		trail->BeginGhostTrailEffect();
	}

}

void ACBP_WarLoadSkel::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

// 안쓸꺼라서 일부로 비어놓음 -> 터지는 것을 방지하기 위함
void ACBP_WarLoadSkel::Action()
{

}
void ACBP_WarLoadSkel::EquipOrUnEquip()
{

}

void ACBP_WarLoadSkel::ActionDropping(bool& Success)
{

}
