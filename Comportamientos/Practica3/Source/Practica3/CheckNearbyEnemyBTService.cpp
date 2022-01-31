// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckNearbyEnemyBTService.h"
#include "WaypointAIController.h"

void UCheckNearbyEnemyBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AWaypointAIController* AIEnemyController = Cast<AWaypointAIController>(OwnerComp.GetOwner());
	AIEnemyController->CheckNearbyEnemy();
}