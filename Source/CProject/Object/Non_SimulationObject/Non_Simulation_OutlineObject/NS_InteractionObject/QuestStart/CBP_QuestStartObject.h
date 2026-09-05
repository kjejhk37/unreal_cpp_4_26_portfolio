// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/NS_InteractionObject/CBP_NS_InteractionObject.h"
#include "CBP_QuestStartObject.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API ACBP_QuestStartObject : public ACBP_NS_InteractionObject
{
	GENERATED_BODY()
	
public:
	ACBP_QuestStartObject();
	virtual void BeginPlay() override;
protected:
	void Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType) override;
	virtual void Tick(float DeltaTime) override;
public:
	// CBPI_Interaction 인터페이스
	void Interaction(AActor* const InteractionActor, bool& Success, AActor*& ResultActor) override;
	void SetLock(bool inLock) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Set") class UParticleSystem* StartParticle;
	UPROPERTY(EditDefaultsOnly, Category = "Quest") TSubclassOf<class ACBP_QuestActor> questActorClass;

};
