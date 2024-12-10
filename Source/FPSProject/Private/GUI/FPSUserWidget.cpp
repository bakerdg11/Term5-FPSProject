// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/FPSUserWidget.h"

void UFPSUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetHealthBar(1.0f);
	SetKillsText(0);

	
	/*
	if (ButtonWidgetPrefab)
	{
		for (int i = 0; i < 4; i++)
		{
			UUserWidget* widget = CreateWidget(this, ButtonWidgetPrefab);
			ButtonContainer->AddChildToVerticalBox(widget);

			UButtonWidget* button = Cast<UButtonWidget>(widget); // GetComponent from Unity
			button->SetText(i);
		}
	}
	*/

}



void UFPSUserWidget::SetHealthBar(float percentage)
{
	if (!HealthBar) return;

	HealthBar->SetPercent(percentage);
}

void UFPSUserWidget::SetKillsText(int amount)
{
	if (!KillsText) return;

	UIKills += amount;
	KillsText->SetText(FText::FromString("Kills: " + FString::FromInt(UIKills)));

}
