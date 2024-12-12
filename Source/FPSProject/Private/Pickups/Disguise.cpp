// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/Disguise.h"

// Sets default values
ADisguise::ADisguise()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!DisguiseMeshComponent)
	{
		DisguiseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DisguiseMesh"));
		DisguiseMeshComponent->SetupAttachment(CollisionComponent);

	}
}

// Called when the game starts or when spawned
void ADisguise::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADisguise::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ADisguise::OnCollect()
{
	Super::OnCollect();

	UE_LOG(LogTemp, Warning, TEXT("Disguise Collect Called"));

	// Access the HUD and update the disguise text
	if (AFPSHUD* HUD = Cast<AFPSHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD()))
	{
		UFPSUserWidget* UserWidget = HUD->GetUserWidget();
		if (UserWidget && UserWidget->DisguisedText)
		{
			UserWidget->DisguisedText->SetText(FText::FromString("Disguised: Yes"));
		}
	}

	Destroy();
}
