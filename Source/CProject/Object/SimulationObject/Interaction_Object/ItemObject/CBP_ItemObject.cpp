// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/SimulationObject/Interaction_Object/ItemObject/CBP_ItemObject.h"
#include "Character/CBP_Character.h"

#include  "Macro/MyMacro.h"

ACBP_ItemObject::ACBP_ItemObject()
{

}
void ACBP_ItemObject::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ACBP_ItemObject::BeginPlay()
{
	Super::BeginPlay();
}

void ACBP_ItemObject::Set_Simul_ComponentsBase(EMeshType newMeshType, ESimulationType newSimulationType, ECollisionType newInteractionType)
{
	Super::Set_Simul_ComponentsBase(newMeshType, newSimulationType, newInteractionType);
}

void ACBP_ItemObject::Interaction(AActor* const InteractionActor, bool& Success, AActor*& ResultActor)
{
	Super::Interaction(InteractionActor, Success, ResultActor);

	Success = false;

	if (auto* character = Cast<ACBP_Character>(InteractionActor))
	{
		bool canAddItem;
		character->CanAddItem(itemName, canAddItem);

		if (canAddItem == false) return;

		character->AddInventory(canAddItem, this, Success);
		
		if (Success)
		{
			DestroyActor(this);

			Success = true;
			ResultActor = nullptr;
			return;
		}
	}
}
