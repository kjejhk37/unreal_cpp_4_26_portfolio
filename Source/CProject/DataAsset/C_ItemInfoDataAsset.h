// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Struct/SItem.h"

#include "C_ItemInfoDataAsset.generated.h"


UCLASS()
class CPROJECT_API UC_ItemInfoDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable) void GetItemInfo(EItemName const itemName, F_ItemInfo& result);

public:
	UPROPERTY(EditAnywhere) TArray<F_ItemInfo> itemInfoDatas;
	
};
