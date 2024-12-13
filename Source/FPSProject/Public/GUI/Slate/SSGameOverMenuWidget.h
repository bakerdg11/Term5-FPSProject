// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/FPSHUD.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class FPSPROJECT_API SSGameOverMenuWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSGameOverMenuWidget)
		{}
		SLATE_ARGUMENT(TWeakObjectPtr<class AFPSHUD>, OwningHUD);
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	TWeakObjectPtr<class AFPSHUD> OwningHUD;

	FReply OnReplayGameClicked() const;
	FReply OnQuitClicked() const;


};
