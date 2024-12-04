// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/FPSHUD.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class FPSPROJECT_API SSettingsWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSettingsWidget)
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<class AFPSHUD>, OwningHUD)
	SLATE_END_ARGS()

	/** Constructs this widget with InArguments */
	void Construct(const FArguments& InArgs);

	TWeakObjectPtr<class AFPSHUD> OwningHUD;

	FReply OnResumeClicked() const;
	FReply OnSoundClicked() const;
	FReply OnQuitClicked() const;
};
