// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/C_CharacterInfoDataAsset.h"

void UC_CharacterInfoDataAsset::GetCharacterInfo(ECharacterName characterName, F_CharacterInfo& result)
{
	for (auto data : characterInfoDatas)
	{
		if (data.characterName == characterName)
		{
			result = data;
			return;
		}
	}
}