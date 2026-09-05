// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/C_WeaponCoolTimeDataAsset.h"

void UC_WeaponCoolTimeDataAsset::GetWeaponCoolTime(ECharacterName const characterName, TMap<ESkillType, F_WeaponSkillCoolTIme>& result)
{
	if (coolTimeData.Find(characterName) == nullptr) return;

	TArray<F_WeaponSkillCoolTIme> resultTemp = coolTimeData[characterName].skillCoolTime;

	TMap<ESkillType, F_WeaponSkillCoolTIme> resultMapTemp;

	for (F_WeaponSkillCoolTIme data : resultTemp)
	{
		if (resultMapTemp.Find(data.skillType) == nullptr)
		{
			resultMapTemp.Add(data.skillType, data);
		}
		else
		{
			resultMapTemp[data.skillType] = data;
		}
	}

	result = resultMapTemp;
}