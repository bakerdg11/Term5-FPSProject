// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "GUI/ButtonWidget.h"
#include "FPSUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_API UFPSUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override; // User Widgets version of BeginPlay

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* IntelText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DisguisedText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* KillsText;

	UFUNCTION()
	void SetHealthBar(float percentage);

	UFUNCTION()
	void SetDisguisedText(bool bIsDisguised);

	UFUNCTION()
	void SetIntelText(bool bIntelAcquired);

	UFUNCTION()
	void SetKillsText(int amount);

private:
	int UIKills;
	
};
