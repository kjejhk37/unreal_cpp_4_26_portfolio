// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/C_MontageDataAsset.h"

void UC_MontageDataAsset::GetSkillMontageData(ESkillType const skillType, F_WeaponSkillMontage& result)
{
	for (auto data : SkillMontageDatas)
	{
		if (data.SkillType == skillType)
		{
			result = data;
			return;
		}
	}
}

void UC_MontageDataAsset::GetMontageData(ECharacterState const state, int const combo, F_MontageData& result)
{
	for (auto data : MontageDatas)
	{
		if (data.CharacterState == state && data.Combo == combo)
		{
			result = data;
			return;
		}
	}
}