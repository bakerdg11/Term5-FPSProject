// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/FPSHUD.h"
#include "Widgets/SWeakWidget.h"

void AFPSHUD::BeginPlay()
{
	Super::BeginPlay();

	
	ShowMainMenu();

	//ShowGameMenu(startingGameWidget);

	//ShowSettingsMenu();
}



void AFPSHUD::DrawHUD()
{
	Super::DrawHUD();

	if (!CrosshairTexture) return;

	// 1. Calculate the center point on the screen
	FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f); //ClipX and ClipY gives you your centre of the screen. *0.5 puts it at centre. 

	// 2. Set the crosshair pivot to the center
	float CrosshairHalfWidth = (CrosshairTexture->GetSurfaceWidth() * 0.5f);
	float CrosshairHalfHeight = (CrosshairTexture->GetSurfaceHeight() * 0.0f);
	FVector2D CrosshairDrawPos(Center.X - CrosshairHalfWidth, Center.Y - CrosshairHalfHeight);

	// 3. Draw the crosshair
	FCanvasTileItem TileItem(CrosshairDrawPos, CrosshairTexture->GetResource(), FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);
}



// MAIN MENU
void AFPSHUD::ShowMainMenu()
{
	if (GEngine && GEngine->GameViewport)
	{
		mainMenuWidget = SNew(SMainMenuWidget).OwningHUD(this);
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(mainMenuWidgetContainer, SWeakWidget).PossiblyNullContent(mainMenuWidget.ToSharedRef()));
	
		if (PlayerOwner)
		{
			PlayerOwner->bShowMouseCursor = true;
			PlayerOwner->SetInputMode(FInputModeUIOnly());
		}
	
	}
}

void AFPSHUD::RemoveMainMenu()
{
	if (GEngine && GEngine->GameViewport && mainMenuWidgetContainer.IsValid())
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(mainMenuWidgetContainer.ToSharedRef());

		if (PlayerOwner)
		{
			PlayerOwner->bShowMouseCursor = false;
			PlayerOwner->SetInputMode(FInputModeGameOnly());
		}
	}
}


// SETTINGS MENU
void AFPSHUD::ShowSettingsMenu()
{
	if (GEngine && GEngine->GameViewport)
	{
		settingsWidget = SNew(SSettingsWidget).OwningHUD(this);
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(settingsWidgetContainer, SWeakWidget).PossiblyNullContent(settingsWidget.ToSharedRef()));
	
		if (PlayerOwner)
		{
			PlayerOwner-> bShowMouseCursor = true;
			PlayerOwner->SetInputMode(FInputModeUIOnly());
		}
	}
}

void AFPSHUD::RemoveSettingsMenu()
{
	if (GEngine && GEngine->GameViewport && settingsWidgetContainer.IsValid())
	{

		GEngine->GameViewport->RemoveViewportWidgetContent(settingsWidgetContainer.ToSharedRef());

		if (PlayerOwner)
		{
			PlayerOwner->bShowMouseCursor = false;
			PlayerOwner->SetInputMode(FInputModeGameOnly());
		}
	}
}

void AFPSHUD::ShowGameMenu(TSubclassOf<UFPSUserWidget> newGameWidget)
{
	if (gameWidgetContainer)
	{
		gameWidgetContainer->RemoveFromParent();
		gameWidgetContainer = nullptr;
	}

	if (newGameWidget)
	{
		gameWidgetContainer = CreateWidget<UFPSUserWidget>(GetWorld(), newGameWidget);
		gameWidgetContainer-> AddToViewport();
	}
}
