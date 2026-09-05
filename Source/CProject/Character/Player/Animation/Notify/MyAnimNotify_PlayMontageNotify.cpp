// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimNotify_PlayMontageNotify.h"
#include "Logger/Logger.h"

UMyAnimNotify_PlayMontageNotify::UMyAnimNotify_PlayMontageNotify()
{
	NotifyName = FName("Test");
}

FString UMyAnimNotify_PlayMontageNotify::GetNotifyName_Implementation() const
{
	return NotifyName.ToString();
}

void UMyAnimNotify_PlayMontageNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

}