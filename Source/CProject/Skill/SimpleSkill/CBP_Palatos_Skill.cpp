// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SimpleSkill/CBP_Palatos_Skill.h"
#include "Components/WidgetComponent.h"
#include "Character/CBP_Character.h"
#include "Character/AICharacter/CBP_AICharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Macro/MyMacro.h"
#include "Macro/KismetMacro.h"

#include "Logger/Logger.h"


ACBP_Palatos_Skill::ACBP_Palatos_Skill()
{

}

void ACBP_Palatos_Skill::BeginPlay()
{
	Super::BeginPlay();

}

void ACBP_Palatos_Skill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (isPlay == false) return;

	curTime += DeltaTime;

	if (ACBP_Character* character = Cast<ACBP_Character>(GetInstigator()))
	{
		if (character->isPressedSkill[skillType] == false || character->isGuard == false)
		{
			SetEnd();
		}

		if (isChargeType == false) return;
		float palatosStartY = -(PalatosLenght * (PalatosNum - 1)) / 2;

		if (curTime < ChargeTime) return;

		curTime = 0;
		if (attackSkillClass == nullptr) return;
		if (count * 2 > PalatosNum) return;


		TArray<int> willSpawnPalatonsNums;

		int value1;
		int value2;

		if (PalatosNum % 2 == 1)
		{
			value1 = (PalatosNum / 2) + count;
			value2 = (PalatosNum / 2) - count;

			willSpawnPalatonsNums.AddUnique(value1);
			willSpawnPalatonsNums.AddUnique(value2);
		}
		else
		{
			value1 = (PalatosNum / 2) + count;
			value2 = (PalatosNum / 2) - count +1;

			willSpawnPalatonsNums.AddUnique(value1);
			willSpawnPalatonsNums.AddUnique(value2);
		}

		for (int i : willSpawnPalatonsNums)
		{
			ACBP_Skill* skill;
			character->SkillSpawn(attackSkillClass, skill, skillType);
			if (skill == nullptr) continue;

			ACBP_SimpleProjectileSkill* projectileSkill = Cast<ACBP_SimpleProjectileSkill>(skill);
			if (projectileSkill == nullptr) continue;

			projectileSkill->startPointer = FVector(0, palatosStartY + PalatosLenght * i, 0);
			projectileSkill->endPointer = FVector(PalatosMoveLenght, palatosStartY + PalatosLenght * i, 0);
			projectileSkill->delayTime = DelayTime;
			projectileSkill->moveSpeed = MoveSpeed;

			projectileSkill->damage = damage;
			projectileSkill->attackType = attackType;
			projectileSkill->attackHitType = attackHitType;
			projectileSkill->pushVector = pushVector;

			projectileSkill->SetSpawn(this);

			spawnPalatos.Add(projectileSkill);
		}
	
		count++;
	}

}

void ACBP_Palatos_Skill::Play(bool const InSuccess, bool& Success)
{
	Success = InSuccess;

	SetStart();
	isPlay = true;
	curTime = 0;
	count = 0;
}

void ACBP_Palatos_Skill::SetSpawn(AActor* centerActor)
{
	AActor* result_CenterActor = centerActor;

	if (centerActor == nullptr)
		result_CenterActor = GetInstigator();

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

	(worldEndPosition - worldStartPosition).ToDirectionAndLength(PalatosVelocity, PalatosMoveLenght);

}

void ACBP_Palatos_Skill::SetStart()
{
	// 스킬이 시작되었을때 즉 한번 딜레이를 하고 나서 진짜로 스킬이 시작되었을떄 발동
	if (ACBP_Character* character = Cast<ACBP_Character>(GetInstigator()))
	{
		if (ACBP_AICharacter* AICharacter = Cast<ACBP_AICharacter>(GetInstigator()))
		{
			AICharacter->Guard_GaugeBar->SetVisibility(true);
		}

		character->isGuard = true;
		character->GetCharacterMovement()->MaxWalkSpeed = 0;
//		character->canMoveBase = false;

		if (isChargeType == false)
		{
			float palatosStartY = -(PalatosLenght * (PalatosNum - 1)) / 2;

			for (int i = 0 ; i< PalatosNum ; i++)
			{
				ACBP_Skill* skill;
				character->SkillSpawn(attackSkillClass, skill, skillType);
				if (skill == nullptr) continue;

				ACBP_SimpleProjectileSkill* projectileSkill = Cast<ACBP_SimpleProjectileSkill>(skill);
				if (projectileSkill == nullptr) continue;

				projectileSkill->startPointer = FVector(0, palatosStartY + PalatosLenght * i, 0);
				projectileSkill->endPointer = FVector(PalatosMoveLenght, palatosStartY + PalatosLenght * i, 0);
				projectileSkill->delayTime = DelayTime;
				projectileSkill->moveSpeed = MoveSpeed;

				projectileSkill->damage = damage;
				projectileSkill->attackType = attackType;
				projectileSkill->attackHitType = attackHitType;
				projectileSkill->pushVector = pushVector;

				projectileSkill->SetSpawn(this);

				spawnPalatos.Add(projectileSkill);
			}

		}
	}
}
void ACBP_Palatos_Skill::SetEnd()
{
	// 스킬이 끝났을떄 발동
	if (ACBP_Character* character = Cast<ACBP_Character>(GetInstigator()))
	{
		if (ACBP_AICharacter* AICharacter = Cast<ACBP_AICharacter>(GetInstigator()))
		{
			AICharacter->Guard_GaugeBar->SetVisibility(false);
		}

		character->isGuard = false;
		character->GetCharacterMovement()->MaxWalkSpeed = 600;
		character->canMoveBase = true;

		if (SetEndMontage != nullptr)
		{
			character->ClearMontageDelegate();
			character->MontageDelegate = FString("ReSetState");
			character->PlayAnimMontage(SetEndMontage);
			character->AddMontageEndedDelegate();

			character->characterState = ECharacterState::Skill;
		}

		for (ACBP_Skill* skill : spawnPalatos)
		{
			bool InSuccess = true;
			bool OutSuccess = false;
			skill->Play(InSuccess, OutSuccess);
		}

		DestroyActor(this);
	}
}

