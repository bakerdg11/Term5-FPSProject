// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectibles/Collectible.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/FPSHUD.h"
#include "GameFramework/Actor.h"
#include "Disguise.generated.h"

UCLASS()
class FPSPROJECT_API ADisguise : public ACollectible
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADisguise();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnCollect() override;

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* DisguiseMeshComponent;

};
