// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/CBP_QuestActor.h"
#include "Object/Non_SimulationObject/Non_Simulation_OutlineObject/NS_InteractionObject/PortalObject/CBP_PortalObject.h"

#include "Sub_Quest/CBP_Sub_QuestActor.h"

#include "Macro/MyMacro.h"
#include "Macro/KismetMacro.h"

#include "Logger/Logger.h"

ACBP_QuestActor::ACBP_QuestActor()
{
	PrimaryActorTick.bCanEverTick = true;

}


void ACBP_QuestActor::BeginPlay()
{
	Super::BeginPlay();

}

void ACBP_QuestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACBP_QuestActor::StartQuest()
{
	SetSpawnedAllActors();
	SetLinkActors();
	SetBeginPlayAllActors();
	SpawnSubQuest();

	if (ACBP_Player* player = Cast<ACBP_Player>(Questcharacter))
	{
		player->QuestInterfaceUpdate();
	}
}

void ACBP_QuestActor::EndQuest()
{
	KismetDelay(TEXT("EndQuestDelayTime"), this, EndDelayTime);
}

void ACBP_QuestActor::EndQuestDelayTime()
{
	SpawnNextQuest();

	if (ACBP_Player* player = Cast<ACBP_Player>(Questcharacter))
	{
		player->QuestInterfaceUpdate();
	}

	DestroyActor(this);
}

void ACBP_QuestActor::MissionSuccess(AActor* interactionActor)
{

}

void ACBP_QuestActor::StageClear(AActor* StageActor)
{

}

void ACBP_QuestActor::AddSubQuestData(ACBP_QuestActor* new_SubQuest)
{
	SpawnedSubQuests.Add(new_SubQuest);
}

void ACBP_QuestActor::CompleteSubQuest(ACBP_QuestActor* subQuest)
{
	if (SpawnedSubQuests.Contains(subQuest) == true) SpawnedSubQuests.Remove(subQuest);

	if (ACBP_Player* player = Cast<ACBP_Player>(Questcharacter))
	{
		player->QuestInterfaceUpdate();
	}

	if (SpawnedSubQuests.Num() == 0) EndQuest();


}

/* =========================================================================================================*/

void ACBP_QuestActor::SpawnNextQuest()
{
	if (nextQuests.IsValidIndex(0) == false)
	{
		SetDeleteSpawnedActors_All();
		SpawnReward();

		ACBP_Player* player = Cast<ACBP_Player>(Questcharacter);
		ACBP_Sub_QuestActor* subQuestActor = Cast<ACBP_Sub_QuestActor>(this);

		if (player != nullptr && subQuestActor == nullptr)
		{
			if (player->curQuestActors.Contains(this) == true)
			{
				player->curQuestActors.Remove(this);
			}
		}

		return;
	}

	SetDeleteSpawnedActors_Count();

	TSubclassOf<ACBP_QuestActor> nextQuestClass = nextQuests[0];
	nextQuests.RemoveAt(0);

	ACBP_QuestActor* nextQuestActor;
	FActorSpawnParameters param;

	SpawnActorUseClass(nextQuestActor, nextQuestClass, param);
	nextQuestActor->nextQuests = nextQuests;
	nextQuestActor->SpawnedKeys = SpawnedKeys;
	nextQuestActor->SpawnedPortals = SpawnedPortals;
	nextQuestActor->SpawnedRemotes = SpawnedRemotes;
	nextQuestActor->SpawnedStages = SpawnedStages;
	nextQuestActor->SpawnedAnimations = SpawnedAnimations;
	nextQuestActor->SpawnedChests = SpawnedChests;
	nextQuestActor->Questcharacter = Questcharacter;

	nextQuestActor->StartQuest();

	SpawnReward();

	ACBP_Player* player = Cast<ACBP_Player>(Questcharacter);
	ACBP_Sub_QuestActor* subQuestActor = Cast<ACBP_Sub_QuestActor>(this);

	if (player != nullptr && subQuestActor == nullptr)
	{
		if (player->curQuestActors.Contains(this) == true)
		{
			player->curQuestActors.Remove(this);
			player->curQuestActors.Add(nextQuestActor);
		}
	}

}

void ACBP_QuestActor::SpawnSubQuest()
{
	for (auto data : SubQuests)
	{
		if (Cast<ACBP_Sub_QuestActor>(data.GetDefaultObject()) == nullptr) continue;

		ACBP_Sub_QuestActor* subQuest;
		FActorSpawnParameters param;
		SpawnActorUseClass(subQuest, data, param);

		subQuest->SetUpQuest(this);
		SpawnedSubQuests.Add(subQuest);
		subQuest->Questcharacter = Questcharacter;
		subQuest->StartQuest();
	}
}

void ACBP_QuestActor::SpawnQuestActor(F_QuestActor_BaseStruct const data)
{
	AActor* spawnedActor;
	
	FTransform trasnform;
	FActorSpawnParameters param;

	trasnform.SetLocation(data.actorLocation);
	trasnform.SetRotation(FQuat(data.actorRotator));
	trasnform.SetScale3D(data.actorScale);

	SpawnActorUseClass_Transform(spawnedActor, data.actorClass, trasnform, param);
	if (spawnedActor == nullptr) return;
	

	F_QuestActor_DeleteCountStruct DeleteData;
	DeleteData.actor = spawnedActor;
	DeleteData.count = data.deleteCount;

	SpawnedNormalActor.Add(DeleteData);
}

void ACBP_QuestActor::SpawnQuestActor(F_QuestActor_TextInterfaceStruct const data)
{

	ACBP_InterfaceActor* spawnedActor;

	FTransform trasnform;
	FActorSpawnParameters param;

	trasnform.SetLocation(data.actorLocation);
	trasnform.SetRotation(FQuat(data.actorRotator));
	trasnform.SetScale3D(data.actorScale);

	SpawnActorUseClass_Transform(spawnedActor, data.actorClass, trasnform, param);
	if (spawnedActor == nullptr) return;

	spawnedActor->Line_1_Text = data.Line_1_Text;
	spawnedActor->Line_2_Text = data.Line_2_Text;
	spawnedActor->Line_3_Text = data.Line_3_Text;
	spawnedActor->Line_4_Text = data.Line_4_Text;

	spawnedActor->SetActorLocation(data.actorLocation);
	spawnedActor->SetActorRotation(data.actorRotator);
	spawnedActor->SetActorScale3D(data.actorScale);

//	Logger::Print(spawnedActor->Line_1_Text.ToString());

	F_QuestActor_DeleteCountStruct DeleteData;
	DeleteData.actor = spawnedActor;
	DeleteData.count = data.deleteCount;

	SpawnedTextInterfaceActor.Add(DeleteData);
}

void ACBP_QuestActor::SpawnQuestActor(F_QuestActor_KeyStruct const data)
{
	if (SpawnedKeys.Contains(data.MyType) == true)
	{
		if(IsValid(SpawnedKeys[data.MyType].actor) == true) return;
	}

	ACBP_KeyObject* SpawnedActor;

	FTransform trasnform;
	FActorSpawnParameters param;

	trasnform.SetLocation(data.actorLocation);
	trasnform.SetRotation(FQuat(data.actorRotator));
	trasnform.SetScale3D(data.actorScale);

	SpawnActorUseClass_Transform(SpawnedActor, data.ActorClass, trasnform, param);
	if (SpawnedActor == nullptr) return;

	SpawnedActor->widgetName = data.widgetName;
	SpawnedActor->isOnceInteraction = data.isOnceInteraction;
	SpawnedActor->DirectInputType = data.DirectInputType;

	F_QuestActor_DeleteCountStruct DeleteData;
	DeleteData.actor = SpawnedActor;
	DeleteData.count = data.deleteCount;

	MapAdd(SpawnedKeys, data.MyType, DeleteData);
}

void ACBP_QuestActor::SpawnQuestActor(F_QuestActor_PortalStruct const data)
{
	if (SpawnedPortals.Contains(data.MyType) == true)
	{
		if (IsValid(SpawnedPortals[data.MyType].actor) == true) return;
	}

	ACBP_PortalObject* SpawnedActor;

	FTransform trasnform;
	FActorSpawnParameters param;

	trasnform.SetLocation(data.actorLocation);
	trasnform.SetRotation(FQuat(data.actorRotator));
	trasnform.SetScale3D(data.actorScale);

	SpawnActorUseClass_Transform(SpawnedActor, data.ActorClass, trasnform, param);
	if (SpawnedActor == nullptr) return;

	SpawnedActor->widgetName = data.widgetName;
	SpawnedActor->portalType = data.movePortalType;
	SpawnedActor->nextPos = data.portalPos;
	SpawnedActor->nextLevel = data.portalLevelName;
	// 링크하는 포탈은 나중에 

	SpawnedActor->isOnceInteraction = data.isOnceInteraction;
	SpawnedActor->DirectInputType = data.DirectInputType;

	F_QuestActor_DeleteCountStruct DeleteData;
	DeleteData.actor = SpawnedActor;
	DeleteData.count = data.deleteCount;

	MapAdd(SpawnedPortals, data.MyType, DeleteData);
}

void ACBP_QuestActor::SpawnQuestActor(F_QuestActor_RemoteStruct const data)
{
	if (SpawnedRemotes.Contains(data.MyType) == true)
	{
		if (IsValid(SpawnedRemotes[data.MyType].actor) == true) return;
	}

	ACBP_RemoteObject* SpawnedActor;

	FTransform trasnform;
	FActorSpawnParameters param;

	trasnform.SetLocation(data.actorLocation);
	trasnform.SetRotation(FQuat(data.actorRotator));
	trasnform.SetScale3D(data.actorScale);

	SpawnActorUseClass_Transform(SpawnedActor, data.ActorClass, trasnform, param);
	if (SpawnedActor == nullptr) return;

	// 여기에 정보 기입
	
	
	// 여기에 정보 기입

	SpawnedActor->widgetName = data.widgetName;
	SpawnedActor->isOnceInteraction = data.isOnceInteraction;
	SpawnedActor->DirectInputType = data.DirectInputType;

	F_QuestActor_DeleteCountStruct DeleteData;
	DeleteData.actor = SpawnedActor;
	DeleteData.count = data.deleteCount;

	MapAdd(SpawnedRemotes, data.MyType, DeleteData);

}

void ACBP_QuestActor::SpawnQuestActor(F_QuestActor_StageStruct const data)
{
	if (SpawnedStages.Contains(data.MyType) == true)
	{
		if (IsValid(SpawnedStages[data.MyType].actor) == true) return;
	}

	ACBP_StageStart_Object* SpawnedActor;

	FTransform trasnform;
	FActorSpawnParameters param;

	trasnform.SetLocation(data.actorLocation);
	trasnform.SetRotation(FQuat(data.actorRotator));
	trasnform.SetScale3D(data.actorScale);

	SpawnActorUseClass_Transform(SpawnedActor, data.ActorClass, trasnform, param);
	if (SpawnedActor == nullptr) return;

	SpawnedActor->allStageData = data.all_Stagedatas;
	// 잠글 액터들은 나중에


	SpawnedActor->widgetName = data.widgetName;
	SpawnedActor->isOnceInteraction = data.isOnceInteraction;
	SpawnedActor->DirectInputType = data.DirectInputType;

	SpawnedActor->StageTime = data.StageTime;

	F_QuestActor_DeleteCountStruct DeleteData;
	DeleteData.actor = SpawnedActor;
	DeleteData.count = data.deleteCount;

	MapAdd(SpawnedStages, data.MyType, DeleteData);

}

void ACBP_QuestActor::SpawnQuestActor(F_QuestActor_AnimationStruct const data)
{
	if (SpawnedAnimations.Contains(data.MyType) == true)
	{
		if (IsValid(SpawnedAnimations[data.MyType].actor) == true) return;
	}

	ACBP_AnimationObject* SpawnedActor;

	FTransform trasnform;
	FActorSpawnParameters param;

	trasnform.SetLocation(data.actorLocation);
	trasnform.SetRotation(FQuat(data.actorRotator));
	trasnform.SetScale3D(data.actorScale);

	SpawnActorUseClass_Transform(SpawnedActor, data.ActorClass, trasnform, param);
	if (SpawnedActor == nullptr) return;

	SpawnedActor->ActorEndRotator = data.ActorEndRotator;
	SpawnedActor->StartTransform = data.StartTransform;
	SpawnedActor->EndTransform = data.EndTransform;
	SpawnedActor->playTime = data.PlayTime;

	SpawnedActor->widgetName = data.widgetName;
	SpawnedActor->isOnceInteraction = data.isOnceInteraction;
	SpawnedActor->DirectInputType = data.DirectInputType;

	F_QuestActor_DeleteCountStruct DeleteData;
	DeleteData.actor = SpawnedActor;
	DeleteData.count = data.deleteCount;

	MapAdd(SpawnedAnimations, data.MyType, DeleteData);
}

void ACBP_QuestActor::SpawnQuestActor(F_QuestActor_ChestBoxStruct const data)
{
	if (SpawnedChests.Contains(data.MyType) == true)
	{
		if (IsValid(SpawnedChests[data.MyType].actor) == true) return;
	}

	ACBP_ChestBox* SpawnedActor;

	FTransform trasnform;
	FActorSpawnParameters param;

	trasnform.SetLocation(data.actorLocation);
	trasnform.SetRotation(FQuat(data.actorRotator));
	trasnform.SetScale3D(data.actorScale);

	SpawnActorUseClass_Transform(SpawnedActor, data.ActorClass, trasnform, param);
	if (SpawnedActor == nullptr) return;

	// 여기에 정보 기입
	SpawnedActor->contents = data.contents;

	// 여기에 정보 기입

	SpawnedActor->widgetName = data.widgetName;
	SpawnedActor->DirectInputType = data.DirectInputType;

	F_QuestActor_DeleteCountStruct DeleteData;
	DeleteData.actor = SpawnedActor;
	DeleteData.count = data.deleteCount;

	MapAdd(SpawnedChests, data.MyType, DeleteData);
}

void ACBP_QuestActor::SpawnQuestActor(F_QuestActor_AttackTerrainStruct const data)
{
	ACBP_AttackTerrainObject* spawnedActor;

	FTransform trasnform;
	FActorSpawnParameters param;

	trasnform.SetLocation(data.actorLocation);
	trasnform.SetRotation(FQuat(data.actorRotator));
	trasnform.SetScale3D(data.actorScale);

	SpawnActorUseClass_Transform(spawnedActor, data.ActorClass, trasnform, param);
	if (spawnedActor == nullptr) return;
	spawnedActor->inEndLocation = data.EndLocation;
	spawnedActor->inEndRotator = data.EndRotation;
	spawnedActor->damage = data.damage;

	F_QuestActor_DeleteCountStruct DeleteData;
	DeleteData.actor = spawnedActor;
	DeleteData.count = data.deleteCount;

	SpawnedAttackTerrains.Add(DeleteData);

}


/* ===================================================== private =============================================================*/
void ACBP_QuestActor::SetDeleteSpawnedActors_Count()
{
	
#define DeleteSpawnedActorsMacro(NameType_None,Datas)										\
	for (TPair<decltype(NameType_None), F_QuestActor_DeleteCountStruct>& data : Datas)		\
	{																						\
		if (data.Value.count == 0 ||  data.Value.actor == nullptr) 							\
		{																					\
			DestroyActor(data.Value.actor);													\
			Datas.Remove(data.Key);	continue;												\
		}																					\
																							\
		if(data.Value.count > 0) data.Value.count--;										\
	};																						\

	DeleteSpawnedActorsMacro(EKeyNameTypes::None,SpawnedKeys);
	DeleteSpawnedActorsMacro(EPortalNameTypes::None, SpawnedPortals);
	DeleteSpawnedActorsMacro(ERemoteNameType::None, SpawnedRemotes);
	DeleteSpawnedActorsMacro(EStageNameType::None, SpawnedStages);
	DeleteSpawnedActorsMacro(EAnimationNameType::None, SpawnedAnimations);
	DeleteSpawnedActorsMacro(EChestNameType::None, SpawnedChests);


	// SpawnedAttackTerrains
	TArray<int> willDeleteActorNums;

	for (int i = 0 ; i < SpawnedAttackTerrains.Num() ; i++)
	{
		if (SpawnedAttackTerrains[i].count == 0 || SpawnedAttackTerrains[i].actor == nullptr)
		{
			DestroyActor(SpawnedAttackTerrains[i].actor);
			willDeleteActorNums.Add(i);
			continue;
		}
		
		if(SpawnedAttackTerrains[i].count > 0)
		{
			SpawnedAttackTerrains[i].count--;
		}
	}

	for (int willDeleteNum : willDeleteActorNums)
	{
		if (SpawnedAttackTerrains.IsValidIndex(willDeleteNum) == true)
			SpawnedAttackTerrains.RemoveAt(willDeleteNum);
	}

	willDeleteActorNums.Empty();

	for (int i = 0; i < SpawnedNormalActor.Num(); i++)
	{
		if (SpawnedNormalActor[i].count == 0 || SpawnedNormalActor[i].actor == nullptr)
		{
			DestroyActor(SpawnedNormalActor[i].actor);
			willDeleteActorNums.Add(i);
			continue;
		}
		
		if(SpawnedNormalActor[i].count > 0)
		{
			SpawnedNormalActor[i].count--;
		}
	}

	for (int willDeleteNum : willDeleteActorNums)
	{
		if (SpawnedNormalActor.IsValidIndex(willDeleteNum) == true)
			SpawnedNormalActor.RemoveAt(willDeleteNum);
	}

	willDeleteActorNums.Empty();

	for (int i = 0; i < SpawnedTextInterfaceActor.Num(); i++)
	{
		if (SpawnedTextInterfaceActor[i].count == 0 || SpawnedTextInterfaceActor[i].actor == nullptr)
		{
			DestroyActor(SpawnedTextInterfaceActor[i].actor);
			willDeleteActorNums.Add(i);
			continue;
		}
		
		if(SpawnedNormalActor[i].count > 0)
		{
			SpawnedNormalActor[i].count--;
		}
	}

	for (int willDeleteNum : willDeleteActorNums)
	{
		if (SpawnedTextInterfaceActor.IsValidIndex(willDeleteNum) == true)
			SpawnedTextInterfaceActor.RemoveAt(willDeleteNum);
	}
	
}

void ACBP_QuestActor::SetDeleteSpawnedActors_All()
{
#define AllDeleteSpawnedActorsMacro(NameType_None,Datas)										\
	for (TPair<decltype(NameType_None), F_QuestActor_DeleteCountStruct>& data : Datas)		\
	{																						\
		if(data.Value.count >= 0){															\
		if(data.Value.actor != nullptr){DestroyActor(data.Value.actor);	}													\
		if(Datas.Contains(data.Key) == true) Datas.Remove(data.Key);				}												\
	};																						\

	AllDeleteSpawnedActorsMacro(EKeyNameTypes::None, SpawnedKeys);
	AllDeleteSpawnedActorsMacro(EPortalNameTypes::None, SpawnedPortals);
	AllDeleteSpawnedActorsMacro(ERemoteNameType::None, SpawnedRemotes);
	AllDeleteSpawnedActorsMacro(EStageNameType::None, SpawnedStages);
//	AllDeleteSpawnedActorsMacro(EAnimationNameType::None, SpawnedAnimations);

	for (TPair<EAnimationNameType, F_QuestActor_DeleteCountStruct>& data : SpawnedAnimations)		
	{																						
		if (data.Value.count >= 0)
		{
			if (data.Value.actor != nullptr) 
			{
				DestroyActor(data.Value.actor);
			}

			if (SpawnedAnimations.Contains(data.Key) == true)
			{
				SpawnedAnimations.Remove(data.Key);
			}
		}												
	};

	TArray<EChestNameType> willDeletes;

	for (TPair<EChestNameType, F_QuestActor_DeleteCountStruct>& data : SpawnedChests)
	{
		if (data.Value.count >= 0)
		{
			AActor* valueActor = data.Value.actor;
			EChestNameType dataKey = data.Key;

			if (valueActor != nullptr)
			{
				if (IsValid(valueActor) == true)
				{
					valueActor->Destroy();
				}
			}

			willDeletes.Add(dataKey);
		}
	};

	for (EChestNameType data : willDeletes)
	{
		if (SpawnedChests.Contains(data) == true)
		{
			SpawnedChests.Remove(data);
		}
	}


	// SpawnedAttackTerrains
	TArray<int> willDeleteActorNums;

	for (int i = 0; i < SpawnedAttackTerrains.Num(); i++)
	{
		if (SpawnedAttackTerrains[i].count >= 0)
		{
			DestroyActor(SpawnedAttackTerrains[i].actor);
			willDeleteActorNums.Add(i);
		}
	}

	for (int willDeleteNum : willDeleteActorNums)
	{
		if(SpawnedAttackTerrains.IsValidIndex(willDeleteNum) == true)
			SpawnedAttackTerrains.RemoveAt(willDeleteNum);
	}

	willDeleteActorNums.Empty();

	for (int i = 0; i < SpawnedNormalActor.Num(); i++)
	{
		if (SpawnedNormalActor[i].count >= 0)
		{
			DestroyActor(SpawnedNormalActor[i].actor);
			willDeleteActorNums.Add(i);
		}
	}

	for (int willDeleteNum : willDeleteActorNums)
	{
		if(SpawnedNormalActor.IsValidIndex(willDeleteNum) == true)
			SpawnedNormalActor.RemoveAt(willDeleteNum);
	}


	willDeleteActorNums.Empty();

	for (int i = 0; i < SpawnedTextInterfaceActor.Num(); i++)
	{
		if (SpawnedTextInterfaceActor[i].count >= 0)
		{
			DestroyActor(SpawnedTextInterfaceActor[i].actor);
			willDeleteActorNums.Add(i);
		}
	}

	for (int willDeleteNum : willDeleteActorNums)
	{
		if (SpawnedTextInterfaceActor.IsValidIndex(willDeleteNum) == true)
			SpawnedTextInterfaceActor.RemoveAt(willDeleteNum);
	}
}


/* ============================================= StartQuest 에 쓸것 ==================================================== */
void ACBP_QuestActor::SetSpawnedAllActors()
{
	for (auto data : SpawnActors) SpawnQuestActor(data);

	for (auto data : SpawnTextInterfaceActors) SpawnQuestActor(data);
	for (auto data : SpawnAttackTerrains) SpawnQuestActor(data);

	for (auto& data : SpawnKeys)		{ data.Value.MyType = data.Key; SpawnQuestActor(data.Value);}
	for (auto& data : SpawnPotals)		{ data.Value.MyType = data.Key; SpawnQuestActor(data.Value);}
	for (auto& data : SpawnRemotes)		{ data.Value.MyType = data.Key; SpawnQuestActor(data.Value);}
	for (auto& data : SpawnStages)		{ data.Value.MyType = data.Key; SpawnQuestActor(data.Value);}
	for (auto& data : SpawnAnimations)	{ data.Value.MyType = data.Key; SpawnQuestActor(data.Value);}
	for (auto& data : SpawnChestBoxs)	{ data.Value.MyType = data.Key; SpawnQuestActor(data.Value);}
	
}

void ACBP_QuestActor::SetLinkActors() 
{
	for (auto& data : SpawnedKeys)
	{
		ACBP_KeyObject* keyData = Cast<ACBP_KeyObject>(data.Value.actor);
		if (keyData == nullptr) continue;

		keyData->SetQuest(this);

		for (auto linkData : SpawnKeys[data.Key].LinkType_Key)			keyData->WillLockActors.AddUnique(SpawnedKeys[linkData].actor);
		for (auto linkData : SpawnKeys[data.Key].LinkType_Portal)		keyData->WillLockActors.AddUnique(SpawnedPortals[linkData].actor);
		for (auto linkData : SpawnKeys[data.Key].LinkType_Remote)		keyData->WillLockActors.AddUnique(SpawnedRemotes[linkData].actor);
		for (auto linkData : SpawnKeys[data.Key].LinkType_Stage)		keyData->WillLockActors.AddUnique(SpawnedStages[linkData].actor);
		for (auto linkData : SpawnKeys[data.Key].LinkType_Animation)	keyData->WillLockActors.AddUnique(SpawnedAnimations[linkData].actor);
		for (auto linkData : SpawnKeys[data.Key].LinkType_Chest)		keyData->WillLockActors.AddUnique(SpawnedChests[linkData].actor);
	}

	for (auto& data : SpawnedPortals)
	{
		ACBP_PortalObject* PortalData = Cast<ACBP_PortalObject>(data.Value.actor);
		if (PortalData == nullptr) continue;

		PortalData->SetQuest(this);


		for (auto linkData : SpawnPotals[data.Key].LinkPortalType) PortalData->nextPortalObject = Cast<ACBP_PortalObject>(SpawnedPortals[linkData].actor);
	}

	for (auto& data : SpawnedRemotes)
	{
		ACBP_RemoteObject* RemoteData = Cast<ACBP_RemoteObject>(data.Value.actor);
		if (RemoteData == nullptr) continue;

		RemoteData->SetQuest(this);


		for (auto linkData : SpawnRemotes[data.Key].LinkType_Key)		RemoteData->RemoteTargetActors.AddUnique(SpawnedKeys[linkData].actor);
		for (auto linkData : SpawnRemotes[data.Key].LinkType_Portal)	RemoteData->RemoteTargetActors.AddUnique(SpawnedPortals[linkData].actor);
		for (auto linkData : SpawnRemotes[data.Key].LinkType_Remote)	RemoteData->RemoteTargetActors.AddUnique(SpawnedRemotes[linkData].actor);
		for (auto linkData : SpawnRemotes[data.Key].LinkType_Stage)		RemoteData->RemoteTargetActors.AddUnique(SpawnedStages[linkData].actor);
		for (auto linkData : SpawnRemotes[data.Key].LinkType_Animation) RemoteData->RemoteTargetActors.AddUnique(SpawnedAnimations[linkData].actor);
		for (auto linkData : SpawnRemotes[data.Key].LinkType_Chest)		RemoteData->RemoteTargetActors.AddUnique(SpawnedChests[linkData].actor);
	}

	for (auto& data : SpawnedStages)
	{
		ACBP_StageStart_Object* StageData = Cast<ACBP_StageStart_Object>(data.Value.actor);
		if (StageData == nullptr) continue;

		StageData->SetQuest(this);

		for (auto linkData : SpawnStages[data.Key].LinkType_Key)		StageData->WillLockActors.AddUnique(SpawnedKeys[linkData].actor);
		for (auto linkData : SpawnStages[data.Key].LinkType_Portal)		StageData->WillLockActors.AddUnique(SpawnedPortals[linkData].actor);
		for (auto linkData : SpawnStages[data.Key].LinkType_Remote)		StageData->WillLockActors.AddUnique(SpawnedRemotes[linkData].actor);
		for (auto linkData : SpawnStages[data.Key].LinkType_Stage)		StageData->WillLockActors.AddUnique(SpawnedStages[linkData].actor);
		for (auto linkData : SpawnStages[data.Key].LinkType_Animation)	StageData->WillLockActors.AddUnique(SpawnedAnimations[linkData].actor);
		for (auto linkData : SpawnStages[data.Key].LinkType_Chest)		StageData->WillLockActors.AddUnique(SpawnedChests[linkData].actor);
	}

}
void ACBP_QuestActor::SetBeginPlayAllActors() 
{
	for (auto& data : SpawnedKeys)
	{
		ACBP_KeyObject* DataActor = Cast<ACBP_KeyObject>(data.Value.actor);
		if (DataActor == nullptr) continue;
		DataActor->BeginPlay();
	}

	for (auto& data : SpawnedPortals)
	{
		ACBP_PortalObject* DataActor = Cast<ACBP_PortalObject>(data.Value.actor);
		if (DataActor == nullptr) continue;
		DataActor->BeginPlay();
	}

	for (auto& data : SpawnedRemotes)
	{
		ACBP_RemoteObject* DataActor = Cast<ACBP_RemoteObject>(data.Value.actor);
		if (DataActor == nullptr) continue;
		DataActor->BeginPlay();
	}

	for (auto& data : SpawnedStages)
	{
		ACBP_StageStart_Object* DataActor = Cast<ACBP_StageStart_Object>(data.Value.actor);
		if (DataActor == nullptr) continue;
		DataActor->BeginPlay();
	}

	for (auto& data : SpawnedAnimations)
	{
		ACBP_AnimationObject* DataActor = Cast<ACBP_AnimationObject>(data.Value.actor);
		if (DataActor == nullptr) continue;
		DataActor->BeginPlay();
	}

	for (auto& data : SpawnedChests)
	{
		ACBP_ChestBox* DataActor = Cast<ACBP_ChestBox>(data.Value.actor);
		if (DataActor == nullptr) continue;
		DataActor->BeginPlay();
	}

	for (auto& data : SpawnedAttackTerrains)
	{
		ACBP_AttackTerrainObject* DataActor = Cast<ACBP_AttackTerrainObject>(data.actor);
		if (DataActor == nullptr) continue;
		DataActor->WorkAttackTerrain();

	}


}

void ACBP_QuestActor::SpawnReward()
{
	for (F_QuestActor_ChestBoxStruct data : RewardChestBox)
	{
		ACBP_ChestBox* SpawnedActor;

		FTransform trasnform;
		FActorSpawnParameters param;

		trasnform.SetLocation(data.actorLocation);
		trasnform.SetRotation(FQuat(data.actorRotator));
		trasnform.SetScale3D(data.actorScale);

		SpawnActorUseClass_Transform(SpawnedActor, data.ActorClass, trasnform, param);
		if (SpawnedActor == nullptr) continue;

		SpawnedActor->contents = data.contents;

		SpawnedActor->widgetName = data.widgetName;
		SpawnedActor->DirectInputType = data.DirectInputType;

		SpawnedActor->BeginPlay();

	}

	for (F_QuestActor_BaseStruct data : RewardActors)
	{
		AActor* SpawnedActor;

		FTransform trasnform;
		FActorSpawnParameters param;

		trasnform.SetLocation(data.actorLocation);
		trasnform.SetRotation(FQuat(data.actorRotator));
		trasnform.SetScale3D(data.actorScale);

		SpawnActorUseClass_Transform(SpawnedActor, data.actorClass, trasnform, param);
		if (SpawnedActor == nullptr) continue;

	}

}