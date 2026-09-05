// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/C_GunInfoDataAsset.h"

void UC_GunInfoDataAsset::GetGunInfo(EWeaponName const weaponName, F_GunTypeInfo& result)
{
	for (auto data : gunInfoDatas)
	{
		if (data.WeapoName == weaponName)
		{
			result = data;
			return;
		}
	}
}