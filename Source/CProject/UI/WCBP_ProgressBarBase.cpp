// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WCBP_ProgressBarBase.h"
#include "Components/CanvasPanel.h"
#include "Components/ProgressBar.h"



void UWCBP_ProgressBarBase::UpdateProgressBar(float curHp, float maxHp)
{
	UProgressBar* progressBar = Cast<UProgressBar>(GetWidgetFromName(FName("HP_ProgressBar")));
	if (progressBar == nullptr) return;

	progressBar->SetPercent(curHp / maxHp);
}
