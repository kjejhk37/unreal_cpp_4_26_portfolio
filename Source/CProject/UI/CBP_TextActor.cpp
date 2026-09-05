// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CBP_TextActor.h"
#include "Components/WidgetComponent.h"
#include "WCBP_TextBase.h"
#include "Kismet/GameplayStatics.h"

#include "Macro/MyMacro.h"
#include "Macro/KismetMacro.h"

// Sets default values
ACBP_TextActor::ACBP_TextActor()
{

//	PrimaryActorTick.bCanEverTick = true;

	auto* const widgetClass = StaticLoadClass(UWCBP_TextBase::StaticClass(), this, TEXT("WidgetBlueprint'/Game/CBP_Data/UI/WBP_Text.WBP_Text_C'"));

	CreateDefaultSubobjectAuto(text);
	text->SetupAttachment(GetRootComponent());

	text->SetWidgetSpace(EWidgetSpace::Screen);
	text->SetWidgetClass(widgetClass);


}

void ACBP_TextActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACBP_TextActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACBP_TextActor::SetTextBox(FString Instring, FVector IntextBaseColor, FVector2D Inpos, float IntextBaseAlpha, bool InisTextAnimation, float Intime, FVector2D Inspeed)
{
	UWCBP_TextBase* textBase = Cast<UWCBP_TextBase>(text->GetUserWidgetObject());
	if (textBase == nullptr) return;
	textBase->SetTextBox(Instring, IntextBaseColor, Inpos, IntextBaseAlpha, InisTextAnimation, Intime, Inspeed);

	KismetDelay(TEXT("DestoryThisActor"), this, Intime);
}

void ACBP_TextActor::DestoryThisActor()
{
	DestroyActor(this);
}

void ACBP_TextActor::SetTextFont(float fontSize)
{
	UWCBP_TextBase* textBase = Cast<UWCBP_TextBase>(text->GetUserWidgetObject());
	if (textBase == nullptr) return;


	textBase->SetTextFont(fontSize);
}

void ACBP_TextActor::SetTextOutlineFont(float fontSize)
{
	UWCBP_TextBase* textBase = Cast<UWCBP_TextBase>(text->GetUserWidgetObject());
	if (textBase == nullptr) return;

	textBase->SetTextOutlineFont(fontSize);
}