// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/C_WeaponSocketDataAsset.h"

void UC_WeaponSocketDataAsset::GetWeaponSocket(bool const isPairWeapon, ECharacterName const characterName, F_WeaponSocket& result)
{
	if (isPairWeapon)
	{
		for (auto data : PairWeaponSocketDatas)
		{
			if (data.CharacterName == characterName)
			{
				result = data;
				return;
			}
		}
		return;
	}

	for (auto data : SocketDatas)
	{
		if (data.CharacterName == characterName)
		{
			result = data;
			return;
		}
	}
}