// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BTT_GetRandomLocation.h"

EBTNodeResult::Type UBTT_GetRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// 1. Get random pointn on nav mesh
	NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	if (NavArea) {
		AEnemyAIController* AIOwner = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
		NavArea->K2_GetRandomReachablePointInRadius(GetWorld(), AIOwner->GetPawn()->GetActorLocation(), RandomLocation, 2000.0f);
	}
	else {
		return EBTNodeResult::Failed;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("Random Patrol Location"), RandomLocation);

	// 2. Set the blackboard random patrol location


	// 3. Return if we succeeded or not
	return EBTNodeResult::Succeeded;
}
