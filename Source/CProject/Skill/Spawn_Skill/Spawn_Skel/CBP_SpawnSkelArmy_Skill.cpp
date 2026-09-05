// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Spawn_Skill/Spawn_Skel/CBP_SpawnSkelArmy_Skill.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Macro/MyMacro.h"

#include "Logger/Logger.h"

ACBP_SpawnSkelArmy_Skill::ACBP_SpawnSkelArmy_Skill()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACBP_SpawnSkelArmy_Skill::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}

void ACBP_SpawnSkelArmy_Skill::BeginPlay()
{
	Super::BeginPlay();

}

void ACBP_SpawnSkelArmy_Skill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACBP_SpawnSkelArmy_Skill::Play(bool const InSuccess, bool& Success)
{
	Super::Play(InSuccess, Success);

	if (spawnCharacterClass == nullptr) return;

	ACBP_AICharacter* character;
	FActorSpawnParameters param;

	character = GetWorld()->SpawnActor<ACBP_AICharacter>(spawnCharacterClass, FVector(10000, 10000, 10000), FRotator(0, 0, 0), param);
	character->SpawnerActor = GetInstigator();
	character->SpawnerWeaponActor = GetOwner();

	FVector particlePosition = worldStartPosition - FVector(0, 0, 90);

	if (SpawnParticle != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SpawnParticle, particlePosition,
			FRotator(0, 0, 0), FVector(1, 1, 1), true);
	}

	character->SetActorLocation(worldStartPosition);
	character->SetActorRotation(FRotator(0, startRotatorYaw,0));

	if (ACBP_Character* OwnerCharacter = Cast<ACBP_Character>(GetInstigator()))
	{
		Target = OwnerCharacter->target;
		character->camp = OwnerCharacter->camp;

		if (character->camp == ECamp::Player)
		{
			character->SetActorScale3D(FVector(1.2f));
		}
	}

	character->targetCandidate.Add(Target);
	character->SerchCloseTarget();

	character->SpawnDefaultController();

	if (isSpawnLife)
	{
		character->SetSpawnLifeTime(spawnTime);
	}

	
	character->isSpawnAICharacter = true;
	character->spawnLocalLocation = centerStartPos;

	DestroyActor(this);
}

void ACBP_SpawnSkelArmy_Skill::SetSpawn(AActor* centerActor)
{
//	Super::SetSpawn();

	AActor* result_CenterActor = centerActor;
	
	if (centerActor == nullptr) result_CenterActor = GetInstigator();

	if (result_CenterActor == nullptr) return;

	FVector InstigatorForward = result_CenterActor->GetActorForwardVector();
	FVector InstigatorUp = result_CenterActor->GetActorUpVector();
	FVector InstigatorRight = result_CenterActor->GetActorRightVector();

	worldStartPosition = InstigatorForward * centerStartPos.X +
		InstigatorUp * centerStartPos.Z +
		InstigatorRight * centerStartPos.Y;

	worldStartPosition += result_CenterActor->GetActorLocation();

	FHitResult result;

	UKismetSystemLibrary::CapsuleTraceSingle(
		GetWorld(),
		worldStartPosition + FVector(0, 0, 200),
		worldStartPosition + FVector(0, 0, -200),
		34,88,
		ETraceTypeQuery::TraceTypeQuery7,
		false,
		{},
		EDrawDebugTrace::Type::None,
		result,
		true
	);

	if (result.bBlockingHit == true)
	{
		worldStartPosition = result.Location;
	}

	startRotation = result_CenterActor->GetActorRotation();
	SetActorRotation(startRotation);

	startRotatorYaw += startRotation.Yaw;

	if (ACBP_Character* character = Cast<ACBP_Character>(GetInstigator()))
	{
		Target = character->target;
	}

}
