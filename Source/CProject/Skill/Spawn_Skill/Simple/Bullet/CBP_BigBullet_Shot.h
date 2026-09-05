// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/Spawn_Skill/Simple/Bullet/CBP_BulletType_Skill.h"
#include "CBP_BigBullet_Shot.generated.h"

/**
 * 
 */
UCLASS()
class CPROJECT_API ACBP_BigBullet_Shot : public ACBP_BulletType_Skill
{
	GENERATED_BODY()

public:
	ACBP_BigBullet_Shot();

	void Play(bool const InSuccess, bool& Success)override;
	
private:
	float bulletSpeed = 3500;
};
