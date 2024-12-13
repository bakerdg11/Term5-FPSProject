// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/FPSUserWidget.h"

void UFPSUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetHealthBar(1.0f);
	SetKillsText(0);
}



void UFPSUserWidget::SetHealthBar(float percentage)
{
	if (!HealthBar) return;

	HealthBar->SetPercent(percentage);
}

void UFPSUserWidget::SetDisguisedText(bool bIsDisguised)
{
	if (!DisguisedText) return;

	FString DisguisedState = bIsDisguised ? "Yes" : "No";
	DisguisedText->SetText(FText::FromString("Disguised: " + DisguisedState));
}

void UFPSUserWidget::SetIntelText(bool bIntelAcquired)
{
	if (!IntelText) return;

	FString IntelState = bIntelAcquired ? "Yes" : "No";
	IntelText->SetText(FText::FromString("Intel Acquired: " + IntelState));
}

void UFPSUserWidget::SetKillsText(int amount)
{
	if (!KillsText) return;

	UIKills += amount;
	KillsText->SetText(FText::FromString("Kills: " + FString::FromInt(UIKills)));

}
