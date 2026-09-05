// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CBP_Character.h"
#include "Skill/Spawn_Skill/CBP_Spawn_Skill.h"

#include "CBP_Player.generated.h"


UCLASS()
class CPROJECT_API ACBP_Player : public ACBP_Character
{
	GENERATED_BODY()

public:
	ACBP_Player();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	virtual void ActionDropping(bool& Success) override;
	virtual void ActionDodge() override;
	virtual void Skill(ESkillType InSkillType, bool isPressed) override;

	virtual void SetDie() override;
	virtual void UpdateInterface(EPlayerInterfaceUpdate updateType) override;

	// Interaction
	void Interaction() override;
	void InteractionSelect(float Value)override;

public:
	UFUNCTION(BlueprintCallable, Category = "Dodge") void SetDodgeDirection();
	UFUNCTION(BlueprintCallable, Category = "Dodge") void SetBeforeDodge();
	UFUNCTION(BlueprintCallable, Category = "AI") void StopAIMoveToActor();

public:
	UFUNCTION(BlueprintCallable) void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
	UFUNCTION(BlueprintCallable) void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UFUNCTION(BlueprintCallable) void SerchOnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION(BlueprintCallable) void SerchOnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UPROPERTY(VisibleAnyWhere) class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnyWhere) class UCameraComponent* Camera;
	UPROPERTY(VisibleAnyWhere) class USphereComponent* targetSearchCollision;

public:
	UPROPERTY(BlueprintReadOnly, Category = "Dodge") float dodgeForward;
	UPROPERTY(BlueprintReadOnly, Category = "Dodge") float dodgeRight;

	UPROPERTY(EditDefaultsOnly) TSubclassOf<ACBP_Spawn_Skill> spawnSkillClass;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<ACBP_Character> testTarget;


private:
	void AttackSetBeforeDodge();

public:
	TArray<AActor*> curQuestActors;
	void QuestInterfaceUpdate();


public:
	TArray<AActor*> interacitonActors;	// F키를 위한 것 
	int curInteractionSelectNum = 0;

 /* ============================ Zoom ===================================*/

		// PlayerInterface - Zoom
private:
	void ZoomCameraIn()override;
	void ZoomCameraOut() override;

	// UFUNCTION()안쓰면 Bind 안해줌
	UFUNCTION()
		void Zoom(float const Alpha);

protected:
	UPROPERTY()
		class UTimelineComponent* ZoomTimeline;

	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
		class UCurveFloat* BlendCurveOnZoomIn;

	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
		float BlendTimeOnZoomIn;

	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
		float FieldOfViewOnZoomIn;

	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
		float TargetArmLenghtOnZoomIn;

	UPROPERTY(EditDefaultsOnly, Category = "Zoom")
		FVector SocketOffsetOnZoomIn;;

	float FieldOfView;
	float TargetArmLenght;
	FVector SocketOffset;

	/* ========================= Parkour ==========================*/
private:
	void Parkour() override;
	UPROPERTY(VisibleAnyWhere) class UCBP_ParkourComponent* ParkourComponent;
	
public:
	void CanParkour(bool& outCanParkour);

protected:
	void Landed(FHitResult const& HitResults) override;
	void BaseOnMontageBlendingOut() override;

};
