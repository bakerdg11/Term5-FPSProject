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
	UE_LOG(LogTemp, Warning, TEXT("Level Completed, You Have Escaped!"));
}

