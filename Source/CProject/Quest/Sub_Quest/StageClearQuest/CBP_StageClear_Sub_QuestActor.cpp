// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/Sub_Quest/StageClearQuest/CBP_StageClear_Sub_QuestActor.h"


ACBP_StageClear_Sub_QuestActor::ACBP_StageClear_Sub_QuestActor()
{

}
void ACBP_StageClear_Sub_QuestActor::StartQuest()
{
	Super::StartQuest();

	SetCheckStages();
}

void ACBP_StageClear_Sub_QuestActor::StageClear(AActor* StageActor)
{
	if (will_CheckStage.Contains(StageActor) == true)
	{
		will_CheckStage.Remove(StageActor);
	}

	for (int32 i = will_CheckStage.Num() - 1; i >= 0; --i)
	{
		if (will_CheckStage[i] == nullptr)
		{
			will_CheckStage.RemoveAt(i);
		}
	}

	if (will_CheckStage.Num() == 0)
	{
		EndQuest();
	}
}

void ACBP_StageClear_Sub_QuestActor::SetCheckStages()
{
	will_CheckStage.Empty();

	for (TPair<int, F_QuestActor_CheckStage> pairData : checkStages)
	{
		ACBP_QuestActor* targetMainQuest = nullptr;

		if (pairData.Key == 0)
		{
			targetMainQuest = this;
		}
		else if (pairData.Key > 0)
		{
			targetMainQuest = this;

			for (int i = 0; i < pairData.Key; i++)
			{
				ACBP_Sub_QuestActor* targetSubQuest = Cast<ACBP_Sub_QuestActor>(targetMainQuest);
				if (targetSubQuest == nullptr)
				{
					targetMainQuest = nullptr;
					break;
				}

				targetMainQuest = targetSubQuest->upQuest;
			}
		}

		if (targetMainQuest == nullptr) continue;

		/*=============================================== Stages ============================================================*/
		for (auto data : pairData.Value.StageNameTyps)
		{
			if (targetMainQuest->SpawnedStages.Contains(data) == true)
			{
				will_CheckStage.Add(targetMainQuest->SpawnedStages[data].actor);
			}
		}
	}

	for (AActor* actor : will_CheckStage)
	{
		if (ICBPI_Interaction* interactionActor = Cast<ICBPI_Interaction>(actor))
		{
			interactionActor->SetQuest(this);
		}
	}
}