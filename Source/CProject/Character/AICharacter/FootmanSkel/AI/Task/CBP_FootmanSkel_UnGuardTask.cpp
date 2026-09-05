// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AICharacter/FootmanSkel/AI/Task/CBP_FootmanSkel_UnGuardTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/CBP_AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

#include "Macro/KismetMacro.h"
#include "Logger/Logger.h"

UCBP_FootmanSkel_UnGuardTask::UCBP_FootmanSkel_UnGuardTask()
{

}

EBTNodeResult::Type UCBP_FootmanSkel_UnGuardTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACBP_AICharacter* character = Cast<ACBP_AICharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (character == nullptr) return EBTNodeResult::Type::Succeeded;

	AActor* target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("Target")));
	if (target == nullptr)
	{
		character->Skill(ESkillType::Skill_1, false);
		character->isGuard = false;
		return EBTNodeResult::Type::Succeeded;
	}

	FVector velocity;
	float length;

	(target->GetActorLocation() - character->GetActorLocation()).ToDirectionAndLength(velocity, length);


	if (targetLenght < length)
	{
		character->Skill(ESkillType::Skill_1, false);

		// AI는 Skill에서 값을 안받음(이유는 모름 생서에서 조정은 되지만 삭제와 false조정을 같이 붙여두었어도 삭제는 하지만 조정은 안됨)
		// 대상을 바꾸는 Delta시간동안 문제가 발생하는걸로 예상 이건 답없음
		character->isGuard = false;
	}

	return EBTNodeResult::Type::Succeeded;
}

void UCBP_FootmanSkel_UnGuardTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

}

