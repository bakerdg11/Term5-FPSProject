// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/Slate/SSMainMenuWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMainMenuWidget::Construct(const FArguments& InArgs)
{



	bCanSupportFocus = true;
	OwningHUD = InArgs._OwningHUD;

	const FMargin ContentPadding = FMargin(500.0f, 300.0f);
	const FMargin ButtonPadding = FMargin(10.0f);

	// Text within the menus
	const FText TitleText = FText::FromString("Hitman's Creed");
	const FText PlayText = FText::FromString("Play");
	const FText SettingsText = FText::FromString("Settings");
	const FText QuitText = FText::FromString("Quit");

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
								.OnClicked(this, &SMainMenuWidget::OnPlayClicked)
								[
									SNew(STextBlock)
										.Font(ButtonTextStyle)
										.Text(PlayText)
										.Justification(ETextJustify::Center)
								]
						]
						// Sound Button
						+ SVerticalBox::Slot()
						.Padding(ButtonPadding)
						[
							SNew(SButton)
								.OnClicked(this, &SMainMenuWidget::OnSettingsClicked)
								[
									SNew(STextBlock)
										.Font(ButtonTextStyle)
										.Text(SettingsText)
										.Justification(ETextJustify::Center)
								]
						]
						// Quit Button
						+ SVerticalBox::Slot()
						.Padding(ButtonPadding)
						[
							SNew(SButton)
								.OnClicked(this, &SMainMenuWidget::OnQuitClicked)
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





FReply SMainMenuWidget::OnPlayClicked() const
{
	if (OwningHUD.IsValid()) 
	{
		OwningHUD->RemoveMainMenu();

		OwningHUD->ShowGameMenu(OwningHUD->startingGameWidget);
	}
	return FReply::Handled();
}

FReply SMainMenuWidget::OnSettingsClicked() const
{
	return FReply::Handled();
}

FReply SMainMenuWidget::OnQuitClicked() const
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