// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GUI/Slate/SSettingsWidget.h"
#include "GUI/Slate/SSGameOverMenuWidget.h"
#include "GUI/Slate/SSGameCompleteMenuWidget.h"
#include "Engine/Canvas.h"
#include "GUI/FPSUserWidget.h"
#include "FPSHUD.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_API AFPSHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	// 1. HUD method of making UI
	virtual void DrawHUD() override;

	// 2. Slates method of making UI
	TSharedPtr<class SMainMenuWidget> mainMenuWidget;
	TSharedPtr<class SWidget> mainMenuWidgetContainer;
	TSharedPtr<class SSettingsWidget> settingsWidget;
	TSharedPtr<class SWidget> settingsWidgetContainer;
	TSharedPtr<class SSGameOverMenuWidget> gameOverMenuWidget;
	TSharedPtr<class SWidget> gameOverMenuWidgetContainer;
	TSharedPtr<class SSGameCompleteMenuWidget> gameCompleteMenuWidget;
	TSharedPtr<class SWidget> gameCompleteMenuWidgetContainer;

	void ShowMainMenu();
	void RemoveMainMenu();

	void ShowSettingsMenu();
	void RemoveSettingsMenu();

	void ShowGameOverMenu();
	void RemoveGameOverMenu();

	void ShowGameCompleteMenu();
	void RemoveGameCompleteMenu();

	// 3. UMG method of making UI
	UPROPERTY(EditAnywhere)
	TSubclassOf<UFPSUserWidget> startingGameWidget;

	UPROPERTY()
	UFPSUserWidget* gameWidgetContainer;

	void ShowGameMenu(TSubclassOf<UFPSUserWidget> newGameWidget);
	UFPSUserWidget* GetUserWidget() const;

public:
	void RemoveGameMenu();

protected:
	UPROPERTY(EditDefaultsOnly) // Uproperty allows you to not have to delete pointers once they are removed
	UTexture2D* CrosshairTexture;

};
