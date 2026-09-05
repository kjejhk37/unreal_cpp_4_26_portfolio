// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/MoveSkill/CBP_MoveSkill.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include "Character/CBP_Character.h"

#include "Kismet/GameplayStatics.h"

#include "Macro/MyMacro.h"
#include "Macro/MathMacro.h"
#include "Macro/KismetMacro.h"

#include "UI/CBP_TextActor.h"

ACBP_MoveSkill::ACBP_MoveSkill()
{
	CreateDefaultSubobjectAuto(AttackCollision);
	CreateDefaultSubobjectAuto(particle);

	AttackCollision->SetupAttachment(GetRootComponent());
	particle->SetupAttachment(GetRootComponent());

	AttackCollision->SetCollisionProfileName(FName("Attack"));
	AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACBP_MoveSkill::BeginPlay()
{
	Super::BeginPlay();

	AttackCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentBeginOverlap);

}

void ACBP_MoveSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isPlay == false) return;

	curPlayTime += DeltaTime;

	ACBP_Character* character = Cast<ACBP_Character>(GetInstigator());
	if (character == nullptr) return;

	FVector nextLocation = GetActorLocation() + Velocity * Speed * DeltaTime;

	FHitResult result;

	UKismetSystemLibrary::LineTraceSingle(
		GetWorld(),
		nextLocation + upPos,
		nextLocation + underPos,
		ETraceTypeQuery::TraceTypeQuery7,
		false,
		{},
		EDrawDebugTrace::Type::None,
		result,
		true
	);


	if (result.bBlockingHit == true)
	{
		FVector curCharacterRootLocation = character->GetMesh()->GetSocketLocation(FName("Root"));
		float lenght;
		FVector valocity;
		(result.Location - curCharacterRootLocation).ToDirectionAndLength(valocity, lenght);
		character->AddActorWorldOffset(valocity * lenght, true);
		
	}

	if (curPlayTime >= PlayTime)
	{
		ThisClass::SetEnd();
	}

}

void ACBP_MoveSkill::Play(bool const InSuccess, bool& Success)
{
	Success = InSuccess;

	KismetDelay(TEXT("StartMoveSkill"),this, DelayTime);
}

void ACBP_MoveSkill::SetSpawn(AActor* centerActor)
{
	AActor* result_CenterActor = centerActor;

	if (centerActor == nullptr)
		result_CenterActor = GetInstigator();

	ACBP_Character* character = Cast<ACBP_Character>(GetInstigator());
	if (character == nullptr) return;


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

	float lenght;
	(worldEndPosition - worldStartPosition).ToDirectionAndLength(Velocity, lenght);

	if (PlayTime == 0) PlayTime = 1;

	Speed = lenght / PlayTime;

	Target = character->target;

	SetAttachRules(Rule);
	AttachToComponent(character->center, Rule);

	AttackCollision->SetSphereRadius(character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
}

void ACBP_MoveSkill::SetStart()
{
	// 스킬이 시작되었을때 즉 한번 딜레이를 하고 나서 진짜로 스킬이 시작되었을떄 발동
	curPlayTime = 0;
	isPlay = true;
	AttackCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	particle->Activate();

	ACBP_Character* character = Cast<ACBP_Character>(GetInstigator());
	if (character == nullptr) return;
	character->SetActorRotation(FRotator(0, startRotation.Yaw, 0));
	character->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
void ACBP_MoveSkill::SetEnd()
{
	// 스킬이 끝났을떄 발동
	particle->Deactivate();

	ACBP_Character* character = Cast<ACBP_Character>(GetInstigator());
	if (character == nullptr) return;
	character->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	DestroyActor(this);
}

void ACBP_MoveSkill::StartMoveSkill()
{
	SetStart();
}

void ACBP_MoveSkill::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OverrlapedActors.Contains(OtherActor) == true) return;
	OverrlapedActors.Add(OtherActor);

	ACBP_Character* character = Cast<ACBP_Character>(OtherActor);
	if (character == nullptr) return;
	
	ECharacterDamagedType damageType = ECharacterDamagedType::Failling;
	F_Hp_Update_Value resultDamage;
	character->AddDamage(this, damageType, resultDamage);

	if (damageType == ECharacterDamagedType::Failling) return;

	FVector ParticleLocation;

	TArray<FHitResult> results;

	UKismetSystemLibrary::LineTraceMulti(
		GetWorld(),
		GetActorLocation(),
		OtherActor->GetActorLocation(),
		ETraceTypeQuery::TraceTypeQuery6,
		false,
		{ GetInstigator() },
		EDrawDebugTrace::Type::None,
		results,
		true
	);

	for (FHitResult result : results)
	{
		if (result.GetActor() == OtherActor)
		{
			ParticleLocation = result.Location;
			break;
		}
	}


	if (attackParticle != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), attackParticle, ParticleLocation,
			FRotator(0, 0, 0), FVector(1, 1, 1), true);
	}

	if (attackParticleActorClass != nullptr)
	{
		ACBP_Particle* particleActor;
		FActorSpawnParameters param;

		SpawnActorUseClass(particleActor, attackParticleActorClass, param);
		particleActor->SetActorLocation(ParticleLocation);

		F_ParticleActorData data;
		data.EndDelayTime = 0;
		data.StartDelayTime = 0;

		particleActor->SetParticlesBase({ data });
		particleActor->Play();
	}

	ACBP_TextActor* textActor;
	FActorSpawnParameters param;

	SpawnActorUseClass(textActor, ACBP_TextActor::StaticClass(), param);
	textActor->SetActorLocation(ParticleLocation);

	FVector fontColor = FVector(1, 1, 1);

	if (damageType == ECharacterDamagedType::Guard)
		fontColor = FVector(1, 1, 0);

	textActor->SetTextBox(FString::FromInt(resultDamage.updateValue * resultDamage.updateCount), fontColor);


}