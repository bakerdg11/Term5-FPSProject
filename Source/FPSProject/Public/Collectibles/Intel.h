// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectibles/Collectible.h"
#include "Kismet/GameplayStatics.h"
#include "Player/FPSCharacter.h"
#include "HUD/FPSHUD.h"
#include "Intel.generated.h"


UCLASS()
class FPSPROJECT_API AIntel : public ACollectible
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AIntel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnCollect() override;

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* IntelMeshComponent;

	UPROPERTY(EditAnywhere)
	float RotationRate = 200;

	UPROPERTY(EditAnywhere)
	float OnCollectRotationRate = 1500;

	FTimerHandle DeathTimerHandle;
	void DeathTimerComplete();



};
