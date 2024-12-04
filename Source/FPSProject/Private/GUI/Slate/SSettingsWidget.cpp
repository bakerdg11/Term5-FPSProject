// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/Slate/SSettingsWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSettingsWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	OwningHUD = InArgs._OwningHUD;

	const FMargin ContentPadding = FMargin(500.0f, 300.0f);
	const FMargin ButtonPadding = FMargin(10.0f);

	// Text within the menus
	const FText TitleText = FText::FromString("Settings Menu");
	const FText ResumeText = FText::FromString("Resume");
	const FText SoundText = FText::FromString("Sound");
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
								.OnClicked(this, &SSettingsWidget::OnResumeClicked)
								[
									SNew(STextBlock)
										.Font(ButtonTextStyle)
										.Text(ResumeText)
										.Justification(ETextJustify::Center)
								]
						]
						// Sound Button
						+ SVerticalBox::Slot()
						.Padding(ButtonPadding)
						[
							SNew(SButton)
								.OnClicked(this, &SSettingsWidget::OnSoundClicked)
								[
									SNew(STextBlock)
										.Font(ButtonTextStyle)
										.Text(SoundText)
										.Justification(ETextJustify::Center)
								]
						]
						// Quit Button
						+ SVerticalBox::Slot()
						.Padding(ButtonPadding)
						[
							SNew(SButton)
								.OnClicked(this, &SSettingsWidget::OnQuitClicked)
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

FReply SSettingsWidget::OnResumeClicked() const
{
	if (OwningHUD.IsValid()) {
		OwningHUD->RemoveSettingsMenu();
	}
	return FReply::Handled();
}
FReply SSettingsWidget::OnSoundClicked() const
{
	return FReply::Handled();
}
FReply SSettingsWidget::OnQuitClicked() const
{
	if (OwningHUD.IsValid()) {
		if (APlayerController* PC = OwningHUD->PlayerOwner) {
			PC->ConsoleCommand("quit");
		}
	}
	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
