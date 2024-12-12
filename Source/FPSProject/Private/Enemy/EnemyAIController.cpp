// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyAIController.h"

AEnemyAIController::AEnemyAIController()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!PawnSensing)
	{
		PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	}
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(StartingBehaviorTree);

	if (PawnSensing)
	{
		PawnSensing->OnSeePawn.AddDynamic(this, &AEnemyAIController::OnSeePawn);
	}
}

void AEnemyAIController::OnSeePawn(APawn* PlayerPawn)
{
	AFPSCharacter* Player = Cast<AFPSCharacter>(PlayerPawn);
	if (!Player) return;

	// Check if the player is disguised
	if (Player->IsDisguised())
	{
		// Player is disguised; enemy should not see them
		SetCanSeePlayer(false, nullptr);
		return;
	}

	// Player is not disguised; enemy can see them
	SetCanSeePlayer(true, Player);

	// Start the timer for losing sight of the player
	RunTriggerableTimer();
}

void AEnemyAIController::SetCanSeePlayer(bool SeePlayer, UObject* Player)
{
	UBlackboardComponent* bb = GetBlackboardComponent();
	bb->SetValueAsBool(FName("Can See Player"), SeePlayer);
	if (SeePlayer)
	{
		bb->SetValueAsObject(FName("Player Target"), Player);
	}
}

void AEnemyAIController::RunTriggerableTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(RetriggerableTimerHandle);
	FunctionDelegate.BindUFunction(this, FName("SetCanSeePlayer"), false, GetPawn());
	GetWorld()->GetTimerManager().SetTimer(RetriggerableTimerHandle, FunctionDelegate, PawnSensing->SensingInterval * 2.0f, false);

}
