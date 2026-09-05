// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/Sub_Quest/InteractionQuest/CBP_Interaction_Sub_QuestActor.h"

#include "Interface/CBPI_Interaction.h"

#include "Logger/Logger.h"

ACBP_Interaction_Sub_QuestActor::ACBP_Interaction_Sub_QuestActor()
{

}

void ACBP_Interaction_Sub_QuestActor::StartQuest()
{
	Super::StartQuest();

	SetCheckInteraction();
}

void ACBP_Interaction_Sub_QuestActor::SetCheckInteraction()
{
	will_CheckInteractions.Empty();

	for (TPair<int, F_QuestActor_CheckInteractions> pairData : checkInteractions)
	{
		ACBP_QuestActor* targetMainQuest = this;
		
		if(pairData.Key > 0)
		{
			for (int i = 0; i < pairData.Key; i++)
			{
				ACBP_Sub_QuestActor* targetSubQuest = Cast<ACBP_Sub_QuestActor>(targetMainQuest);
				if (targetSubQuest == nullptr)
				{
					break;
				}

				targetMainQuest = targetSubQuest->upQuest;
			}
		}

		if (targetMainQuest == nullptr) continue;


		/*=============================================== Key ============================================================*/
		for (auto data : pairData.Value.KeyNameTyps)
		{
			if (targetMainQuest->SpawnedKeys.Contains(data) == true)
			{
				will_CheckInteractions.Add(targetMainQuest->SpawnedKeys[data].actor);
			}
		}

		/*=============================================== Portal ============================================================*/
		for (auto data : pairData.Value.PortalNameTyps)
		{
			if (targetMainQuest->SpawnedPortals.Contains(data) == true)
			{
				will_CheckInteractions.Add(targetMainQuest->SpawnedPortals[data].actor);
			}
		}

		/*=============================================== Remote ============================================================*/
		for (auto data : pairData.Value.RemoteNameTyps)
		{
			if (targetMainQuest->SpawnedRemotes.Contains(data) == true)
			{
				will_CheckInteractions.Add(targetMainQuest->SpawnedRemotes[data].actor);
			}
		}

		/*=============================================== Stages ============================================================*/
		for (auto data : pairData.Value.StageNameTyps)
		{
			if (targetMainQuest->SpawnedStages.Contains(data) == true)
			{
				will_CheckInteractions.Add(targetMainQuest->SpawnedStages[data].actor);
			}
		}

		/*=============================================== Animation ============================================================*/
		for (auto data : pairData.Value.AnimationNameTyps)
		{
			if (targetMainQuest->SpawnedAnimations.Contains(data) == true)
			{
				will_CheckInteractions.Add(targetMainQuest->SpawnedAnimations[data].actor);
			}
		}

		/*=============================================== ChestBox ============================================================*/
		for (auto data : pairData.Value.ChestNameTyps)
		{
			if (targetMainQuest->SpawnedChests.Contains(data) == true)
			{
				will_CheckInteractions.Add(targetMainQuest->SpawnedChests[data].actor);
			}
		}
	}

	for (AActor* actor : will_CheckInteractions)
	{

		if (ICBPI_Interaction* interactionActor = Cast<ICBPI_Interaction>(actor))
		{
			interactionActor->SetQuest(this);
		}
	}
}


void ACBP_Interaction_Sub_QuestActor::MissionSuccess(AActor* interactionActor)
{
	Logger::Print("");

	if (will_CheckInteractions.Contains(interactionActor) == true)
	{
		will_CheckInteractions.Remove(interactionActor);
	}

	for (int32 i = will_CheckInteractions.Num() - 1; i >= 0; --i)
	{
		if (will_CheckInteractions[i] == nullptr)
		{
			will_CheckInteractions.RemoveAt(i);
		}
	}

	if (will_CheckInteractions.Num() == 0)
	{
		EndQuest();
	}
}