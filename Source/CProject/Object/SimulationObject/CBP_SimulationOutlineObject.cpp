// Fill out your copyright notice in the Description page of Project Settings.


#include "CBP_SimulationOutlineObject.h"
#include "Macro/MyMacro.h"
#include "Logger/Logger.h"


ACBP_SimulationOutlineObject::ACBP_SimulationOutlineObject()
{

}
void ACBP_SimulationOutlineObject::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}

void ACBP_SimulationOutlineObject::BeginPlay()
{
	Super::BeginPlay();

	SetOutline();
}

void ACBP_SimulationOutlineObject::SetHiddenOutline(bool const newHidden)
{
	switch (meshType)
	{
	case EMeshType::StaticMesh:
		staticOutlineMesh->SetHiddenInGame(newHidden);
		break;
	case EMeshType::SkeletalMesh:
		skeletalMesh->SetHiddenInGame(newHidden);
		break;
	}
}

void ACBP_SimulationOutlineObject::Set_Simul_ComponentsBase(EMeshType newMeshType, ESimulationType newSimulationType, ECollisionType newInteractionType)
{
	Super::Set_Simul_ComponentsBase(newMeshType, newSimulationType, newInteractionType);

	FAttachmentTransformRules const Rules(EAttachmentRule::KeepRelative, true);

	switch (meshType)
	{
	case EMeshType::StaticMesh:
		CreateDefaultSubobjectAuto(staticOutlineMesh);
		staticOutlineMesh->AttachToComponent(staticMesh, Rules);
		staticOutlineMesh->SetCollisionProfileName(FName("NoCollision"));
		break;
	case EMeshType::SkeletalMesh:
		CreateDefaultSubobjectAuto(skeletalOutlineMesh);
		skeletalMesh->AttachToComponent(skeletalMesh, Rules);
		skeletalMesh->SetCollisionProfileName(FName("NoCollision"));
		break;
	}
}

void ACBP_SimulationOutlineObject::SetOutline()
{
	// 얘는 무조건 블루프린트에서 해줘야 됨 안그럼 라인이 많이 꼬임 
	// (materal을 위의것을 가져와야하기 때문에 생성자에서 불가능함 때문에 위의 기본셋팅을 안하면 애가 망가짐
	if (staticMesh == NULL && simulationComponent == NULL && skeletalMesh == NULL)
		return;

	UMaterialInstance* outlineMaterial = LoadObject<UMaterialInstance>(this, TEXT("'/Game/UsingData/Material/Outline/BPM_OutlineMaterail.BPM_OutlineMaterail'"));
	switch (meshType)
	{
	case EMeshType::StaticMesh:
		staticOutlineMesh->SetStaticMesh(staticMesh->GetStaticMesh());
		if (outlineMaterial != NULL)
		{
			//		staticOutlineMesh->GetNumMaterials();
			int instanceNum = staticOutlineMesh->GetNumMaterials();

			for(int i = 0 ; i< instanceNum ; i++)
				staticOutlineMesh->SetMaterial(i, outlineMaterial);
		}
		break;
	case EMeshType::SkeletalMesh:
		skeletalOutlineMesh->SetSkeletalMesh(skeletalMesh->SkeletalMesh);
		if (outlineMaterial != NULL)
		{
			int32 instanceNum = staticOutlineMesh->GetNumMaterials();

			for (int32 i = 0; i < instanceNum; i++)
				skeletalOutlineMesh->SetMaterial(i, outlineMaterial);
		}
		break;
	}


}

