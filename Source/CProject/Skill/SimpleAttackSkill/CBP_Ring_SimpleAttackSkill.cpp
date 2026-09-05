// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SimpleAttackSkill/CBP_Ring_SimpleAttackSkill.h"
#include "Components/SphereComponent.h"

#include "Macro/KismetMacro.h"

#include "Logger/Logger.h"

ACBP_Ring_SimpleAttackSkill::ACBP_Ring_SimpleAttackSkill()
{

}

void ACBP_Ring_SimpleAttackSkill::CorrectComponentSerch(bool& canAttack, AActor* OtherActor)
{
	canAttack = false;

	FVector OtherActorLocation = OtherActor->GetActorLocation();

	if (ACBP_Character* character = Cast<ACBP_Character>(OtherActor))
	{
		OtherActorLocation = character->center->GetComponentLocation();
	}

	FVector SkillActorLocation = AttackComponent->GetComponentLocation();

	FVector ComponentUpVector = AttackComponent->GetUpVector();


	FVector SkillToOtherActorVector = OtherActorLocation - SkillActorLocation;
	float DotUp = 0;
//	(OtherActorLocation - SkillActorLocation).ToDirectionAndLength(SkillToOtherActorVector, DotUp);

	DotUp = FVector::DotProduct(ComponentUpVector, SkillToOtherActorVector);	// 상대적 Up방향 검사
	// Ring 검사법

//	Logger::Print(DotUp,0);
//	Logger::Print(SkillToOtherActorVector,1);
//	Logger::Print(ComponentUpVector,2);



	if (fabsf(DotUp) < upDistance)
	{
		canAttack = true;
	}

	FHitResult result;

	UKismetSystemLibrary::LineTraceSingle(
		GetWorld(),
		GetActorLocation(),
		OtherActor->GetActorLocation(),
		ETraceTypeQuery::TraceTypeQuery7,
		false,
		{ GetInstigator() },
		EDrawDebugTrace::Type::None,
		result,
		true
	);

	if (result.bBlockingHit == true)
	{
		canAttack = false;
	}

}
