// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/Slate/SSGameCompleteMenuWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSGameCompleteMenuWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	OwningHUD = InArgs._OwningHUD;

	const FMargin ContentPadding = FMargin(500.0f, 300.0f);
	const FMargin ButtonPadding = FMargin(10.0f);

	// Text within the menus
	const FText TitleText = FText::FromString("You have successfully escaped with the intel");
	const FText ReplayGameText = FText::FromString("Back To Main Menu");
	const FText QuitText = FText::FromString("Quit Game");

	FSlateFontInfo TitleTextStyle = FCoreStyle::Get().GetFontStyle("EmbassedText");
	TitleTextStyle.Size = 60.0f;

	FSlateFontInfo ButtonTextStyle = TitleTextStyle;
	TitleTextStyle.Size = 40.0f;

	ChildSlot
		[
			SNew(SOverlay)
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill) // Fills the whole screen
				.VAlign(VAlign_Fill)
				[
					SNew(SImage)
						.ColorAndOpacity(FColor::Black)
				]
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(ContentPadding)
				[
					// Title Text
					SNew(SVerticalBox)
						+ SVerticalBox::Slot()
						[
							SNew(STextBlock)
								.Font(TitleTextStyle)
								.Text(TitleText)
								.Justification(ETextJustify::Center)
						]

						// Resume Button
						+ SVerticalBox::Slot()
						.Padding(ButtonPadding)
						[
							SNew(SButton)
								.OnClicked(this, &SSGameCompleteMenuWidget::OnReplayGameClicked)
								[
									SNew(STextBlock)
										.Font(ButtonTextStyle)
										.Text(ReplayGameText)
										.Justification(ETextJustify::Center)
								]
						]

						// Quit Button
						+ SVerticalBox::Slot()
						.Padding(ButtonPadding)
						[
							SNew(SButton)
								.OnClicked(this, &SSGameCompleteMenuWidget::OnQuitClicked)
								[
									SNew(STextBlock)
										.Font(ButtonTextStyle)
										.Text(QuitText)
										.Justification(ETextJustify::Center)
								]
						]
				]
		];

}





FReply SSGameCompleteMenuWidget::OnReplayGameClicked() const
{
	if (OwningHUD.IsValid())
	{
		// Remove the current Game Complete Menu
		OwningHUD->RemoveGameCompleteMenu();

		// Reload the current level
		UWorld* World = OwningHUD->GetWorld();
		if (World)
		{
			FName LevelName = FName(TEXT("FPSMap"));
			UGameplayStatics::OpenLevel(World, LevelName);
		}
	}

	return FReply::Handled();
}

FReply SSGameCompleteMenuWidget::OnQuitClicked() const
{
	if (OwningHUD.IsValid())
	{
		if (APlayerController* PC = OwningHUD->PlayerOwner) {
			PC->ConsoleCommand("quit");
		}
	}
	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
