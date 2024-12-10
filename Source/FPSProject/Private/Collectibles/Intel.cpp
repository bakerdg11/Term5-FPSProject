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
	Super::OnCollect();

	UE_LOG(LogTemp, Warning, TEXT("INTEL Collect Calledd"));

	RotationRate = OnCollectRotationRate;

	//C++ version of delay node
	GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &AIntel::DeathTimerComplete, 0.5f, false);

}

void AIntel::DeathTimerComplete()
{
	AFPSHUD* HUD = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<AFPSHUD>();
	if (!HUD) return;

	HUD->gameWidgetContainer->SetKillsText(Points);

	Destroy();

}
