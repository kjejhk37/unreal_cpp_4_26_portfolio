// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CBP_SimulationObject.h"
#include "CBP_SimulationOutlineObject.generated.h"


UCLASS()
class CPROJECT_API ACBP_SimulationOutlineObject : public ACBP_SimulationObject
{
	GENERATED_BODY()

public:
	ACBP_SimulationOutlineObject();
	void OnConstruction(const FTransform& Transform) override;
	//	virtual void Tick(float DeltaTime) override;
public:
	UFUNCTION(BlueprintCallable, Category = "Set") void SetHiddenOutline(bool const newHidden);

protected:
	virtual void BeginPlay() override;
	void Set_Simul_ComponentsBase(EMeshType newMeshType, ESimulationType newSimulationType, ECollisionType newInteractionType)override;


protected:
	UFUNCTION(BlueprintCallable, Category = "Set Base") void SetOutline();

	UPROPERTY(VisibleAnyWhere) class USkeletalMeshComponent* skeletalOutlineMesh;
	UPROPERTY(VisibleAnyWhere) class UStaticMeshComponent* staticOutlineMesh;

//	UPROPERTY(EditDefaultsOnly, Category = "Outline") class UObject* OutlineMaterial;


};
