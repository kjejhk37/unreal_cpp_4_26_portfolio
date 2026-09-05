// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/C_ItemInfoDataAsset.h"

void UC_ItemInfoDataAsset::GetItemInfo(EItemName const itemName, F_ItemInfo& result)
{
	for (F_ItemInfo itemInfo : itemInfoDatas)
	{
		if (itemInfo.itemName == itemName)
		{
			result = itemInfo;
		}
	}
}