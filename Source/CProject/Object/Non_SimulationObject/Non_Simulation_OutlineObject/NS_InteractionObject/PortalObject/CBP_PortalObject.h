// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/NS_InteractionObject/CBP_NS_InteractionObject.h"
#include "Enums/EInteraction.h"

#include "CBP_PortalObject.generated.h"


UCLASS()
class CPROJECT_API ACBP_PortalObject : public ACBP_NS_InteractionObject
{
	GENERATED_BODY()

public:
	ACBP_PortalObject();
	void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;
protected:
	void Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType) override;


public:
	// CBPI_Interaction 인터페이스
	void Interaction(AActor* const InteractionActor, bool& Success, AActor*& ResultActor) override;
	void SetLock(bool inLock) override;

protected:
	UPROPERTY(VisibleAnywhere) class UParticleSystemComponent* particle;
	UPROPERTY(EditDefaultsOnly, Category = "Set") class UParticleSystem* portalParticle;

public:
	UPROPERTY(EditInstanceOnly, Category = "Set") class ACBP_PortalObject* nextPortalObject;
	UPROPERTY(EditInstanceOnly, Category = "Set") FName nextLevel;
	UPROPERTY(EditInstanceOnly, Category = "Set") FVector nextPos;

	UPROPERTY(EditInstanceOnly, Category = "Set") EPortalType portalType = EPortalType::None;

	void SetBeginPlay();
};
