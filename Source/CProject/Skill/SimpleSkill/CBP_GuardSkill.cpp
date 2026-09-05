// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SimpleSkill/CBP_GuardSkill.h"
#include "Components/WidgetComponent.h"
#include "Character/CBP_Character.h"
#include "Character/AICharacter/CBP_AICharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Macro/MyMacro.h"
#include "Logger/Logger.h"

ACBP_GuardSkill::ACBP_GuardSkill()
{

}

void ACBP_GuardSkill::BeginPlay()
{
	Super::BeginPlay();

}

void ACBP_GuardSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isPlay == false) return;

	if (ACBP_Character* character = Cast<ACBP_Character>(GetInstigator()))
	{
		if (character->isPressedSkill[skillType] == false || character->isGuard == false)
		{
			SetEnd();
		}
	}
}

void ACBP_GuardSkill::Play(bool const InSuccess, bool& Success)
{
	Success = InSuccess;

	SetStart();
	isPlay = true;
}

void ACBP_GuardSkill::SetSpawn(AActor* centerActor)
{
}

void ACBP_GuardSkill::SetStart()
{
	// 스킬이 시작되었을때 즉 한번 딜레이를 하고 나서 진짜로 스킬이 시작되었을떄 발동
	if (ACBP_Character* character = Cast<ACBP_Character>(GetInstigator()))
	{
		if (ACBP_AICharacter* AICharacter = Cast<ACBP_AICharacter>(GetInstigator()))
		{
			AICharacter->Guard_GaugeBar->SetVisibility(true);
		}

		character->isGuard = true;
		character->GetCharacterMovement()->MaxWalkSpeed = 450;
	}
}
void ACBP_GuardSkill::SetEnd()
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

		DestroyActor(this);
	}
}
