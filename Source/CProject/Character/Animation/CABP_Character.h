// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CABP_Character.generated.h"


UCLASS()
class CPROJECT_API UCABP_Character : public UAnimInstance
{
	GENERATED_BODY()

public:
	UCABP_Character();

	virtual void NativeUpdateAnimation(float const DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly)	float speed;
	UPROPERTY(BlueprintReadOnly)	float direction;
	UPROPERTY(BlueprintReadOnly)	float pitch;

	UPROPERTY(BlueprintReadOnly)	bool isMove;
	UPROPERTY(BlueprintReadOnly)	bool isDownFalling = false;
	UPROPERTY(BlueprintReadOnly)	bool isGuard = false;
	UPROPERTY(BlueprintReadOnly)	bool isFalling = false;

	UPROPERTY(BlueprintReadOnly)	FVector TranslationP;
	UPROPERTY(BlueprintReadOnly)	FVector TranslationL;
	UPROPERTY(BlueprintReadOnly)	FVector TranslationR;
	UPROPERTY(BlueprintReadOnly)	FRotator RotationL;
	UPROPERTY(BlueprintReadOnly)	FRotator RotationR;
	UPROPERTY(EditDefaultsOnly)		FName IKBoneL;
	UPROPERTY(EditDefaultsOnly)		FName IKBoneR;



private:
	void TraceForIK(FName const Bone, float& Distance, FRotator& Rotator);

	static int32 const TraceDistance = 35;
	static int32 const InterpSpeed = 50;
	
};
