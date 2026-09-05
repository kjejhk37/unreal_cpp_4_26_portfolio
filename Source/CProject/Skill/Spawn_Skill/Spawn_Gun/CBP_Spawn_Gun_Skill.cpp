// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Spawn_Skill/Spawn_Gun/CBP_Spawn_Gun_Skill.h"
#include "Character/CBP_Character.h"

#include "Macro/MyMacro.h"
#include "Macro/MathMacro.h"
#include "Macro/KismetMacro.h"

#include "Logger/Logger.h"

ACBP_Spawn_Gun_Skill::ACBP_Spawn_Gun_Skill()
{
	CreateDefaultSubobjectAuto(GunMesh);

	GunMesh->SetupAttachment(center);
	GunMesh->SetRelativeRotation(RotatorXYZ(0, 0, -90));
}

void ACBP_Spawn_Gun_Skill::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}

void ACBP_Spawn_Gun_Skill::BeginPlay()
{
	Super::BeginPlay();

	GunMesh->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &ThisClass::GunOnMontageEnded);

}

void ACBP_Spawn_Gun_Skill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	playTime += DeltaTime;

	FVector newLocation = worldStartPosition;

	newLocation.Y += sin(playTime * 1.5f) * 50;
	newLocation.Z += sin(playTime * 0.75f) * 60;

	SetActorLocationAndRotation(newLocation, startRotation);

	if (!endPlay) return;

	endPlayTime += DeltaTime;

	newLocation = GetActorLocation() + FVector(0, 0, endPlayTime * endPlaySpeed);

	SetActorLocation(newLocation);
}

void ACBP_Spawn_Gun_Skill::Shot(bool isDelay)
{
	if (ACBP_Character* character = Cast<ACBP_Character>(GetInstigator()))
	{
		Target = character->target;
	}

	if (isDelay)
	{
		KismetDelay(TEXT("ShotDelegate"), this, delayTime);
	}
	else
		ThisClass::ShotDelegate();
}

void ACBP_Spawn_Gun_Skill::ShotDelegate()
{
	// 한번쏘면 연사하도록 만들었음
	if (!isCharacterSkillStart)
	{
		if (auto* character = Cast<ACBP_Character>(GetInstigator()))
			character->SkillEnd();

		isCharacterSkillStart = true;
	}

	ThisClass::LookAtTarget();
	GunMesh->GetAnimInstance()->Montage_Play(ShotMontage, attackCoolTime * 5);
}

void ACBP_Spawn_Gun_Skill::GunOnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (bInterrupted) return;

	ThisClass::CheckEnd();
}

void ACBP_Spawn_Gun_Skill::CheckEnd()
{
	if (stopShot)
	{
		stopShot = false;
		isCharacterSkillStart = false;
		return;
	}

	attackCount--;
	if (attackCount <= 0)
	{
		if (auto* character = Cast<ACBP_Character>(GetInstigator()))
			character->SkillEnd();

		FLatentActionInfo actionInfo(0, 0, TEXT("SetEnd"), this);
		UKismetSystemLibrary::Delay(GetWorld(), 1.0f, actionInfo);
	}
	else
	{
		Shot(false);
	}
}

void ACBP_Spawn_Gun_Skill::SetEnd()
{
	endPlay = true;

	FLatentActionInfo actionInfo(0, 0, TEXT("DestroyThisActor"), this);
	UKismetSystemLibrary::Delay(GetWorld(), 3.0f, actionInfo);
}

void ACBP_Spawn_Gun_Skill::DestroyThisActor(){DestroyActor(this);}

void ACBP_Spawn_Gun_Skill::GunShot()
{
	FVector start;
	FVector end;

	FVector ShotPos = GunMesh->GetSocketLocation(FName("Shot"));

	start = ShotPos;
	end = ShotPos + (GetActorForwardVector() * attackLength);

	FHitResult result;


	UKismetSystemLibrary::LineTraceSingle(
		GetWorld(),
		start,
		end,
		ETraceTypeQuery::TraceTypeQuery3,
		false,
		{ GetInstigator() },
		EDrawDebugTrace::Type::None,
		result,
		true
	);


}

void ACBP_Spawn_Gun_Skill::LookAtTarget()
{
	if (ACBP_Character* character = Cast<ACBP_Character>(Target))
	{
		startRotation = UKismetMathLibrary::FindLookAtRotation(worldStartPosition, character->center->GetComponentLocation());
	}
}

void ACBP_Spawn_Gun_Skill::SetSpawn(AActor* centerActor)
{
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

	worldEndPosition = InstigatorForward * centerEndPos.X +
		InstigatorUp * centerEndPos.Z +
		InstigatorRight * centerEndPos.Y;

	worldEndPosition += result_CenterActor->GetActorLocation();

	SetActorLocation(worldStartPosition);

	startRotation = UKismetMathLibrary::FindLookAtRotation(worldStartPosition, worldEndPosition);
	SetActorRotation(startRotation);

	if (ACBP_Character* character = Cast<ACBP_Character>(GetInstigator()))
	{
		Target = character->target;
	}
}

void ACBP_Spawn_Gun_Skill::Play(bool const InSuccess, bool& Success)
{
	Super::Play(InSuccess, Success);

	if(Target == nullptr)
		startRotation = UKismetMathLibrary::FindLookAtRotation(worldStartPosition, worldEndPosition);

	Shot(true);
	Success = true;
}