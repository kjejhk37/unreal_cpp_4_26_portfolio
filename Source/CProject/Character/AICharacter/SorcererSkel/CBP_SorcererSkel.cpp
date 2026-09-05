// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/SorcererSkel/CBP_SorcererSkel.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"

#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

#include "UI/CBP_TextActor.h"

#include "Macro/MyMacro.h"
#include "Logger/Logger.h"

ACBP_SorcererSkel::ACBP_SorcererSkel()
{
	GetMesh()->SetRelativeLocation(FVector(0, 0, -100));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	GetCapsuleComponent()->SetCapsuleHalfHeight(100);

	InteractionCollision->SetCollisionProfileName(FName("NoCollision"));
}

void ACBP_SorcererSkel::BeginPlay()
{
	Super::BeginPlay();

	SpawnBaseWeapon(mainWeaponClass, pairWeaponClass);
}

void ACBP_SorcererSkel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (target == nullptr) return;
}

void ACBP_SorcererSkel::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

// 안쓸꺼라서 일부로 비어놓음 -> 터지는 것을 방지하기 위함
void ACBP_SorcererSkel::Action()
{

}
void ACBP_SorcererSkel::EquipOrUnEquip()
{

}

void ACBP_SorcererSkel::SetDeleteSpawnedActor(AActor* InDeleteSpawnedActor)
{
	if (DeleteSpawnedActorParticle != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeleteSpawnedActorParticle, GetActorLocation(),
			FRotator(0, 0, 0), FVector(1, 1, 1), true);
	}

	F_Hp_Update_Value damage;
	damage.curUpdateTick = 0;
	damage.maxUpdateTick = 0;
	damage.updateCount = 100;
	damage.updateValue = 1;

	AddHpUpdate(damage);

	ACBP_TextActor* textActor;
	FActorSpawnParameters param;

	SpawnActorUseClass(textActor, ACBP_TextActor::StaticClass(), param);
	textActor->SetActorLocation(GetActorLocation());

	textActor->SetTextFont(24);
	textActor->SetTextOutlineFont(1);
	textActor->SetTextBox(FString("100"), FVector(1,0,0));

	Super::SetDeleteSpawnedActor(InDeleteSpawnedActor);
}