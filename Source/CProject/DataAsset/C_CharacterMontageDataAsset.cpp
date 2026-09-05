// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/C_CharacterMontageDataAsset.h"

void UC_CharacterMontageDataAsset::GetCharacterMontage(ECharacterMontageName characterMontageName, F_BaseMontageData& result)
{
	for (F_BaseMontageData data : characterMontageDatas)
	{
		if (data.CharacterMontageName == characterMontageName)
		{
			result = data;
		}
	}

}
