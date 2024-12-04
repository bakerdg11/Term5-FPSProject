// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "ButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_API UButtonWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget)) // This allows you to gain access to the buttons in blueprint
	UButton* Button;
	
	UPROPERTY(meta = (BindWidget)) // This allows you to gain access to the buttons in blueprint
	UTextBlock* ButtonText;

	UFUNCTION()
	void SetText(int value);

	UFUNCTION()
	void OnButtonClick();

private:
	int num = -1;

};
