// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/LevelCompleteTrigger.h"

// Sets default values
ALevelCompleteTrigger::ALevelCompleteTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!CollisionComponent)
	{
		CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ALevelCompleteTrigger::BeginOverlap);
		CollisionComponent->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
		RootComponent = CollisionComponent;
	}
}

// Called when the game starts or when spawned
void ALevelCompleteTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelCompleteTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelCompleteTrigger::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Check if the overlapping actor is the player
    if (AFPSCharacter* Player = Cast<AFPSCharacter>(OtherActor))
    {
        // Check if the player has acquired the intel
        if (Player->IntelIsAcquired())
        {
            UE_LOG(LogTemp, Warning, TEXT("Level Completed, You Have Escaped!"));

            // Get the Player Controller
            APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
            if (PlayerController)
            {
                // Get the HUD and display the GameCompleteMenu
                AFPSHUD* HUD = Cast<AFPSHUD>(PlayerController->GetHUD());
                if (HUD)
                {
                    HUD->ShowGameCompleteMenu();
                }
            }

            //Pause the game --------------------------------------------- Needs to be removed when replaying. 
            UGameplayStatics::SetGamePaused(GetWorld(), true);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("You cannot escape without acquiring the intel!"));
        }
    }
}

