// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/CBP_NS_OutlineObject.h"
#include "Macro/MyMacro.h"


ACBP_NS_OutlineObject::ACBP_NS_OutlineObject()
{
	//	PrimaryActorTick.bCanEverTick = true;
}

void ACBP_NS_OutlineObject::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}

void ACBP_NS_OutlineObject::BeginPlay()
{
	Super::BeginPlay();

	SetOutline();

}

/* ======================================== Set ========================================================*/
void ACBP_NS_OutlineObject::SetHiddenOutline(bool const newHidden)
{
	switch (meshType)
	{
	case EMeshType::StaticMesh:
		staticOutlineMesh->SetHiddenInGame(newHidden);
		break;
	case EMeshType::SkeletalMesh:
		skeletalOutlineMesh->SetHiddenInGame(newHidden);
		break;
	}
}


/*========================================= Set Base ====================================================*/
void ACBP_NS_OutlineObject::SetOutline()
{
	if (isOnce == true) return;

	isOnce = true;

	// 얘는 무조건 블루프린트에서 해줘야 됨 안그럼 라인이 많이 꼬임 
// (materal을 위의것을 가져와야하기 때문에 생성자에서 불가능함 때문에 위의 기본셋팅을 안하면 애가 망가짐
	if (staticMesh == NULL && skeletalMesh == NULL)
		return;

	UMaterialInstance* outlineMaterial = LoadObject<UMaterialInstance>(this, TEXT("'/Game/UsingData/Material/Outline/BPM_OutlineMaterail.BPM_OutlineMaterail'"));
	switch (meshType)
	{
	case EMeshType::StaticMesh:
		staticOutlineMesh->SetStaticMesh(staticMesh->GetStaticMesh());
		if (outlineMaterial != NULL)
		{
			int instanceNum = staticOutlineMesh->GetNumMaterials();

			for (int i = 0; i < instanceNum; i++)
				staticOutlineMesh->SetMaterial(i, outlineMaterial);
		}
		break;
	case EMeshType::SkeletalMesh:
		skeletalOutlineMesh->SetSkeletalMesh(skeletalMesh->SkeletalMesh);
		if (outlineMaterial != NULL)
		{
			int32 instanceNum = skeletalOutlineMesh->GetNumMaterials();

			for (int32 i = 0; i < instanceNum; i++)
				skeletalOutlineMesh->SetMaterial(i, outlineMaterial);
		}
		break;
	}
}


/* ======================================== Component Base =========================================*/
void ACBP_NS_OutlineObject::Set_NonSimul_ComponentsBase(EMeshType newMeshType, ECollisionType newInteractionType)
{
	Super::Set_NonSimul_ComponentsBase(newMeshType, newInteractionType);


	switch (meshType)
	{
	case EMeshType::StaticMesh:
		CreateDefaultSubobjectAuto(staticOutlineMesh);
		staticOutlineMesh->SetupAttachment(staticMesh);
		staticOutlineMesh->SetCollisionProfileName(FName("NoCollision"));
		break;
	case EMeshType::SkeletalMesh:
		CreateDefaultSubobjectAuto(skeletalOutlineMesh);
		skeletalOutlineMesh->SetupAttachment(skeletalMesh);
		skeletalOutlineMesh->SetCollisionProfileName(FName("NoCollision"));
		break;
	}

}

