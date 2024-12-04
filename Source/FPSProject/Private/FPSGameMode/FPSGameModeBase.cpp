// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameMode/FPSGameModeBase.h"

void AFPSGameModeBase::StartPlay()
{
	Super::StartPlay();

	//Print to screen
	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("What's Up FPSGameModeBase")); //Generally dev purposes. 



	//Print to output
	//int test = 10;
	//bool boolTest = true;
	//UE_LOG(LogTemp, Warning, TEXT("Test: %i, TestBool: %d, StringText: %s"), test, boolTest);

	// Modern way to print without format specifiers
	//UE_LOGFMT(LogTemp, Warning, "Hello World");
}
