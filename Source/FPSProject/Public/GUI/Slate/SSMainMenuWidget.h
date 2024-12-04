// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/FPSHUD.h"
#include "Widgets/SCompoundWidget.h"

/**
 *
 */
class FPSPROJECT_API SMainMenuWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMainMenuWidget)
		{}
		SLATE_ARGUMENT(TWeakObjectPtr<class AFPSHUD>, OwningHUD)
	SLATE_END_ARGS()

	/** Constructs this widget with InArguments */
	void Construct(const FArguments& InArgs);

	TWeakObjectPtr<class AFPSHUD> OwningHUD;

	FReply OnPlayClicked() const;
	FReply OnSettingsClicked() const;
	FReply OnQuitClicked() const;
};
