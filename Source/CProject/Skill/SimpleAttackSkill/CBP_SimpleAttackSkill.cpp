// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SimpleAttackSkill/CBP_SimpleAttackSkill.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

#include "Character/CBP_Character.h"

#include "Macro/MyMacro.h"
#include "Macro/KismetMacro.h"

#include "Logger/Logger.h"

ACBP_SimpleAttackSkill::ACBP_SimpleAttackSkill()
{
	CreateDefaultSubobjectAuto(AttackComponent);
	AttackComponent->SetupAttachment(GetRootComponent());

	AttackComponent->SetCollisionProfileName(FName("Attack"));
	AttackComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackComponent->SetSphereRadius(100);	// 계산편의성을 위한 값


	CreateDefaultSubobjectAuto(particle);
	particle->SetupAttachment(AttackComponent);

}

void ACBP_SimpleAttackSkill::BeginPlay()
{
	Super::BeginPlay();

	AttackComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentBeginOverlap);

	KismetDelay(TEXT("SetEnd"), this, playDelayTime + playTime);
}

void ACBP_SimpleAttackSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isPlay == false) return;

	curTime += DeltaTime;

	float value = 0;
	if(curTime != 0) value = curTime / playTime;

	float newScale = UKismetMathLibrary::Lerp(StartScale, EndScale, value);

	AttackComponent->SetRelativeScale3D(FVector(newScale));

	if (curTime > playTime)
	{
		SetEnd();
	}
}

void ACBP_SimpleAttackSkill::Play(bool const InSuccess, bool& Success)
{
	Super::Play(InSuccess, Success);


	if (playDelayTime == 0)
	{
		SetStart();
	}
	else
	{
		KismetDelay(TEXT("SetStart"), this, playDelayTime);
	}

}

void ACBP_SimpleAttackSkill::SetSpawn(AActor* centerActor)
{
	Super::SetSpawn(centerActor);

}

void ACBP_SimpleAttackSkill::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (AttackActors.Contains(OtherActor) == true)
		return;

	bool canAttack = false;
	CorrectComponentSerch(canAttack, OtherActor);

	if (canAttack == false) return;

	ACBP_Character* otherCharacter = Cast<ACBP_Character>(OtherActor);
	if (otherCharacter == nullptr) return;

	ACBP_Character* instigatorCharacter = Cast<ACBP_Character>(GetInstigator());
	if (instigatorCharacter == nullptr) return;

	bool bHostile = false;
	instigatorCharacter->IsHostile(otherCharacter->camp, bHostile);
	if (bHostile == false) return;

	TArray<FHitResult> results;

	UKismetSystemLibrary::LineTraceMulti(
		GetWorld(),
		AttackComponent->GetComponentLocation(),
		otherCharacter->GetActorLocation(),
		ETraceTypeQuery::TraceTypeQuery5,
		false,
		{ GetInstigator() },
		EDrawDebugTrace::Type::None,
		results,
		true
	);

	FVector particleLocation = otherCharacter->GetActorLocation();

	for (FHitResult result : results)
	{
		if (result.Actor == OtherActor)
		{
			particleLocation = result.Location;
			break;
		}
	}

	ECharacterDamagedType damageType;
	F_Hp_Update_Value resultDamage;

	otherCharacter->AddDamage(this, damageType, resultDamage);
	if (damageType == ECharacterDamagedType::Failling) return;

	AttackActors.Add(OtherActor);

	SpawnAttackParticle(attackParticle, attackParticleActorClass, particleLocation);

	FVector fontColor = FVector(1, 1, 1);
	float fontSize = 24;

	if (otherCharacter->characterName == ECharacterName::Player)
		fontSize = 30;

	if (damageType == ECharacterDamagedType::Guard)
	{
		fontColor = FVector(1, 1, 0);
		fontSize *= 0.75f;
	}

	SpawnTextActor(FString::FromInt(resultDamage.updateValue * resultDamage.updateCount),
		particleLocation,
		fontColor,
		fontSize);

}

void ACBP_SimpleAttackSkill::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}


void ACBP_SimpleAttackSkill::SetStart()
{
	AttackComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	curTime = 0;
	isPlay = true;

	AttackActors.Empty();
}

void ACBP_SimpleAttackSkill::SetEnd()
{
	AttackComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DestroyActor(this);
}

