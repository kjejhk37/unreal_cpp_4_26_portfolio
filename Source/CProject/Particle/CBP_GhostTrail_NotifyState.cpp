// Fill out your copyright notice in the Description page of Project Settings.


#include "Particle/CBP_GhostTrail_NotifyState.h"
#include "Character/CBP_Character.h"

#include "Macro/MyMacro.h"
#include "Logger/Logger.h"

UCBP_GhostTrail_NotifyState::UCBP_GhostTrail_NotifyState()
{

}

FString UCBP_GhostTrail_NotifyState::GetNotifyName_Implementation() const
{
	return FString("Ghost_Trail_Notify_State");
}

void UCBP_GhostTrail_NotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	curTime = 0;

}

void UCBP_GhostTrail_NotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

}

void UCBP_GhostTrail_NotifyState::NotifyTick(class USkeletalMeshComponent * MeshComp, class UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);


	curTime += FrameDeltaTime;

	if (curTime >= trailInterval)
	{
		curTime = 0;

		ACBP_Character* character = Cast<ACBP_Character>(MeshComp->GetOwner());
		if (character == nullptr) return;

		ACBP_GhostTrail* ghostTrail;

		FActorSpawnParameters param;
		ghostTrail = (character->GetWorld())->SpawnActor<ACBP_GhostTrail>(GhostTrailClass, param);
		if (ghostTrail == nullptr) return;

		ghostTrail->PoseCharacter = character;
		ghostTrail->trailTime = trailTime;

		ghostTrail->BeginGhostTrailEffect();
	}
}
