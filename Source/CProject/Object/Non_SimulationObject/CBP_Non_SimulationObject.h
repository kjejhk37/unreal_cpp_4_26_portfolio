// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enums/EObject.h"
#include "Interface/CBPI_Object.h"
#include "CBP_Non_SimulationObject.generated.h"

UCLASS(Abstract)
class CPROJECT_API ACBP_Non_SimulationObject : public AActor, public ICBPI_Object
{
	GENERATED_BODY()
	
public:	
	ACBP_Non_SimulationObject();
	void OnConstruction(const FTransform& Transform) override;
protected:
	void Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType) override;
	virtual void BeginPlay() override;

public:	
//	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, Category = "Trasnform") void SetScale(FVector const newScale);
	UFUNCTION(BlueprintCallable, Category = "Trasnform") void SetScaleMesh(FVector const newScale);
	UFUNCTION(BlueprintCallable, Category = "Trasnform") void SetPosition(FVector const newPosition);
	UFUNCTION(BlueprintCallable, Category = "Trasnform") void SetRotation(FRotator const newRotator);

	UFUNCTION(BlueprintCallable, Category = "Set") void SetVisible(bool newVisible);

public:
//	UPROPERTY(VisibleAnyWhere) class USceneComponent* DefaultComponent;

	UPROPERTY(VisibleAnyWhere) class USkeletalMeshComponent* skeletalMesh;
	UPROPERTY(VisibleAnyWhere) class UStaticMeshComponent* staticMesh;

	UPROPERTY(BlueprintReadOnly, Category = "Type")EMeshType meshType;

};
