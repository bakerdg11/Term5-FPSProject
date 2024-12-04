// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Logging/Structuredlog.h"
#include "FPSGameModeBase.generated.h" // This has to be last!

/**
 * 
 */
UCLASS()
class FPSPROJECT_API AFPSGameModeBase : public AGameModeBase //AFPS A = Actor. Child of Actor
{
	GENERATED_BODY()
	
public:
	virtual void StartPlay() override;
};
