#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/EngineTypes.h"

#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/NS_InteractionObject/PortalObject/CBP_PortalObject.h"
#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/NS_InteractionObject/Animation_Object/CBP_AnimationObject.h"
#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/NS_InteractionObject/Animation_Object/Remote/CBP_RemoteObject.h"
#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/NS_InteractionObject/StageStart/CBP_StageStart_Object.h"
#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/NS_InteractionObject/Animation_Object/ChestBox/CBP_ChestBox.h"
#include "Object/Non_SimulationObject/CBP_AttackTerrainObject.h"

#include "Object/SimulationObject/Interaction_Object/MoveObject/KeyObject/CBP_KeyObject.h"
#include "UI/CBP_InterfaceActor.h"

#include "Enums/EQuest.h"
#include "Enums/EInteraction.h"

#include "SInteraction.h"

#include "SQuest.generated.h"


USTRUCT(BlueprintType)
struct F_QuestActor_BaseStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TSubclassOf<AActor> actorClass;
	UPROPERTY(EditAnywhere) FVector actorLocation;
	UPROPERTY(EditAnywhere) FRotator actorRotator;
	UPROPERTY(EditAnywhere) FVector actorScale = FVector(1, 1, 1);

	UPROPERTY(EditAnywhere) int deleteCount = 0;
};

USTRUCT(BlueprintType)
struct F_QuestActor_TextInterfaceStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TSubclassOf<ACBP_InterfaceActor> actorClass;
	UPROPERTY(EditAnywhere) FVector actorLocation;
	UPROPERTY(EditAnywhere) FRotator actorRotator;
	UPROPERTY(EditAnywhere) FVector actorScale = FVector(1, 1, 1);

	UPROPERTY(EditAnywhere) FText Line_1_Text;
	UPROPERTY(EditAnywhere) FText Line_2_Text;
	UPROPERTY(EditAnywhere) FText Line_3_Text;
	UPROPERTY(EditAnywhere) FText Line_4_Text;

	UPROPERTY(EditAnywhere) int deleteCount = 0;
};


/* ================================================ Key =================================================*/
USTRUCT(BlueprintType)
struct F_QuestActor_KeyStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TSubclassOf<ACBP_KeyObject> ActorClass;

	UPROPERTY(EditAnywhere) FString widgetName = FString("Key");
	UPROPERTY(EditAnywhere) EKeyNameTypes MyType;

	UPROPERTY(EditAnywhere) FVector actorLocation;
	UPROPERTY(EditAnywhere) FRotator actorRotator;
	UPROPERTY(EditAnywhere) FVector actorScale = FVector(1, 1, 1);

	UPROPERTY(EditAnywhere) bool isOnceInteraction = false;
	UPROPERTY(EditAnywhere) bool DirectInputType = true;

	// 잠글 애들
	UPROPERTY(EditAnywhere) TArray<EKeyNameTypes> LinkType_Key;
	UPROPERTY(EditAnywhere) TArray<EPortalNameTypes> LinkType_Portal;
	UPROPERTY(EditAnywhere) TArray<ERemoteNameType> LinkType_Remote;
	UPROPERTY(EditAnywhere) TArray<EStageNameType> LinkType_Stage;
	UPROPERTY(EditAnywhere) TArray<EAnimationNameType> LinkType_Animation;
	UPROPERTY(EditAnywhere) TArray<EChestNameType> LinkType_Chest;

	UPROPERTY(EditAnywhere) int deleteCount = 0;
};


/* ============================================== Portal ============================================*/
USTRUCT(BlueprintType)
struct F_QuestActor_PortalStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TSubclassOf<ACBP_PortalObject> ActorClass;

	UPROPERTY(EditAnywhere) FString widgetName = FString("Portal");
	UPROPERTY(EditAnywhere) EPortalNameTypes MyType;

	UPROPERTY(EditAnywhere) FVector actorLocation;
	UPROPERTY(EditAnywhere) FRotator actorRotator;
	UPROPERTY(EditAnywhere) FVector actorScale = FVector(1, 1, 1);

	UPROPERTY(EditAnywhere) EPortalType movePortalType;
	UPROPERTY(EditAnywhere) FVector portalPos;
	UPROPERTY(EditAnywhere) FName portalLevelName;

	UPROPERTY(EditAnywhere) TArray<EPortalNameTypes> LinkPortalType;

	UPROPERTY(EditAnywhere) bool isOnceInteraction = false;
	UPROPERTY(EditAnywhere) bool DirectInputType = true;

	UPROPERTY(EditAnywhere) int deleteCount = 0;
};


/* ========================================== Remote ========================================*/
USTRUCT(BlueprintType)
struct F_QuestActor_RemoteStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TSubclassOf<ACBP_RemoteObject> ActorClass;

	UPROPERTY(EditAnywhere) FString widgetName = FString("Remote");
	UPROPERTY(EditAnywhere) ERemoteNameType MyType;

	UPROPERTY(EditAnywhere) FVector actorLocation;
	UPROPERTY(EditAnywhere) FRotator actorRotator;
	UPROPERTY(EditAnywhere) FVector actorScale = FVector(1, 1, 1);

	UPROPERTY(EditAnywhere) bool isOnceInteraction = false;
	UPROPERTY(EditAnywhere) bool DirectInputType = true;

	// 대신 상호작용할 것들
	UPROPERTY(EditAnywhere) TArray<EKeyNameTypes> LinkType_Key;
	UPROPERTY(EditAnywhere) TArray<EPortalNameTypes> LinkType_Portal;
	UPROPERTY(EditAnywhere) TArray<ERemoteNameType> LinkType_Remote;
	UPROPERTY(EditAnywhere) TArray<EStageNameType> LinkType_Stage;
	UPROPERTY(EditAnywhere) TArray<EAnimationNameType> LinkType_Animation;
	UPROPERTY(EditAnywhere) TArray<EChestNameType> LinkType_Chest;


	UPROPERTY(EditAnywhere) int deleteCount = 0;
};

 /* ======================================= Stage =======================================*/
USTRUCT(BlueprintType)
struct F_QuestActor_StageStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TSubclassOf<ACBP_StageStart_Object> ActorClass;

	UPROPERTY(EditAnywhere) FString widgetName = FString("Stage");
	UPROPERTY(EditAnywhere) EStageNameType MyType;

	UPROPERTY(EditAnywhere) FVector actorLocation;
	UPROPERTY(EditAnywhere) FRotator actorRotator;
	UPROPERTY(EditAnywhere) FVector actorScale = FVector(1, 1, 1);

	UPROPERTY(EditAnywhere) bool isOnceInteraction = false;
	UPROPERTY(EditAnywhere) bool DirectInputType = true;

	UPROPERTY(EditAnywhere) TArray<F_SpawnMonsterStageData> all_Stagedatas;
	UPROPERTY(EditAnywhere) float StageTime = 180;

	// 스테이지 시작후 잠그고 클리어후 열것 듯
	UPROPERTY(EditAnywhere) TArray<EKeyNameTypes> LinkType_Key;
	UPROPERTY(EditAnywhere) TArray<EPortalNameTypes> LinkType_Portal;
	UPROPERTY(EditAnywhere) TArray<ERemoteNameType> LinkType_Remote;
	UPROPERTY(EditAnywhere) TArray<EStageNameType> LinkType_Stage;
	UPROPERTY(EditAnywhere) TArray<EAnimationNameType> LinkType_Animation;
	UPROPERTY(EditAnywhere) TArray<EChestNameType> LinkType_Chest;

	UPROPERTY(EditAnywhere) int deleteCount = 0;
};

/* =============================================== Animation ==========================================*/
USTRUCT(BlueprintType)
struct F_QuestActor_AnimationStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TSubclassOf<ACBP_AnimationObject> ActorClass;

	UPROPERTY(EditAnywhere) FString widgetName = FString("Animation");
	UPROPERTY(EditAnywhere) EAnimationNameType MyType;

	UPROPERTY(EditAnywhere) FVector actorLocation;
	UPROPERTY(EditAnywhere) FRotator actorRotator;
	UPROPERTY(EditAnywhere) FVector actorScale = FVector(1, 1, 1);

	UPROPERTY(EditAnywhere) bool isOnceInteraction = false;
	UPROPERTY(EditAnywhere) bool DirectInputType = true;

	UPROPERTY(EditAnywhere) FRotator ActorEndRotator;
	UPROPERTY(EditAnywhere) FTransform StartTransform = FTransform();
	UPROPERTY(EditAnywhere) FTransform EndTransform = FTransform();
	UPROPERTY(EditAnywhere) float PlayTime = 1;

	UPROPERTY(EditAnywhere) int deleteCount = 0;
};

USTRUCT(BlueprintType)
struct F_QuestActor_ChestBoxStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TSubclassOf<ACBP_ChestBox> ActorClass;

	UPROPERTY(EditAnywhere) FString widgetName = FString("ChestBox");
	UPROPERTY(EditAnywhere) EChestNameType MyType;

	UPROPERTY(EditAnywhere) FVector actorLocation;
	UPROPERTY(EditAnywhere) FRotator actorRotator;
	UPROPERTY(EditAnywhere) FVector actorScale = FVector(1, 1, 1);

	UPROPERTY(EditAnywhere) bool DirectInputType = true;

	UPROPERTY(EditAnywhere) TArray<TSubclassOf<AActor>> contents;

	UPROPERTY(EditAnywhere) int deleteCount = 0;
};

/* ================================== AttackTerrain =============================================*/

USTRUCT(BlueprintType)
struct F_QuestActor_AttackTerrainStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TSubclassOf<ACBP_AttackTerrainObject> ActorClass;

	UPROPERTY(EditAnywhere) FVector actorLocation;
	UPROPERTY(EditAnywhere) FRotator actorRotator;
	UPROPERTY(EditAnywhere) FVector actorScale = FVector(1, 1, 1);

	UPROPERTY(EditAnywhere) FVector EndLocation;
	UPROPERTY(EditAnywhere) FRotator EndRotation;
	UPROPERTY(EditAnywhere) F_Hp_Update_Value damage;

	UPROPERTY(EditAnywhere) int deleteCount = 0;
};