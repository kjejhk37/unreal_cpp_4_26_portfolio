// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../Enums/EObject.h"
#include "Interface/CBPI_Object.h"

#include "CBP_SimulationObject.generated.h"

UCLASS(Abstract)
class CPROJECT_API ACBP_SimulationObject : public AActor , public ICBPI_Object
{
	GENERATED_BODY()
	
public:	
	ACBP_SimulationObject();
	void OnConstruction(const FTransform& Transform) override;
	//	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	void Set_Simul_ComponentsBase(EMeshType newMeshType, ESimulationType newSimulationType, ECollisionType newInteractionType)override;

public:	
	UFUNCTION(BlueprintCallable, Category = "Trasnform") void SetScale(FVector const newScale);
	UFUNCTION(BlueprintCallable, Category = "Trasnform") void SetScaleMesh(FVector const newScale);
	UFUNCTION(BlueprintCallable, Category = "Trasnform") void SetPosition(FVector const newPosition);
	UFUNCTION(BlueprintCallable, Category = "Trasnform") void SetRotation(FRotator const newRotator);

	UFUNCTION(BlueprintCallable, Category = "Set") void SetSimulation(bool newSimul);
	UFUNCTION(BlueprintCallable, Category = "Set") void SetVisible(bool newVisible);
	UFUNCTION(BlueprintCallable, Category = "Simulation") void SetImpulse(bool isAtLocation,float power , FVector velocity , FVector Location);


//	UFUNCTION(BlueprintCallable) float Test(bool& newVisible, bool const visible) { newVisible = visible;  return 0; }

public:
	UPROPERTY(VisibleAnyWhere) class USkeletalMeshComponent* skeletalMesh;
	UPROPERTY(VisibleAnyWhere) class UStaticMeshComponent* staticMesh;
	UPROPERTY(VisibleAnyWhere) class UShapeComponent* simulationComponent;

public:
	UPROPERTY(BlueprintReadOnly, Category = "Type")ESimulationType simulationType;
	UPROPERTY(BlueprintReadOnly, Category = "Type")EMeshType meshType;

};
