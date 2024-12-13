// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectibles/Intel.h"


AIntel::AIntel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!IntelMeshComponent)
	{
		IntelMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("IntelMesh"));
		IntelMeshComponent->SetupAttachment(CollisionComponent);

	}
}

// Called when the game starts or when spawned
void AIntel::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AIntel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0, RotationRate * DeltaTime, 0));

}

void AIntel::OnCollect()
{
    // Call the base class implementation, if any
    Super::OnCollect();

    // Log to confirm the function was called
    UE_LOG(LogTemp, Warning, TEXT("INTEL Collect Called"));

    // Update rotation rate for visual feedback
    RotationRate = OnCollectRotationRate;

    // Set a timer to handle the delayed destruction or any other effect
    GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &AIntel::DeathTimerComplete, 0.5f, false);

    // Attempt to get the player character
    AFPSCharacter* Player = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
    if (Player)
    {
        // Update the player's state to indicate intel is acquired
        Player->SetIntelAcquired(true);

        // Access the HUD through the player controller
        AFPSHUD* HUD = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<AFPSHUD>();
        if (HUD)
        {
            // Get the user widget attached to the HUD
            UFPSUserWidget* UserWidget = HUD->GetUserWidget();
            if (UserWidget && UserWidget->IntelText)
            {
                // Update the intel text on the UI
                UserWidget->SetIntelText(true);
            }
        }
    }
}

void AIntel::DeathTimerComplete()
{
	Destroy();
}
