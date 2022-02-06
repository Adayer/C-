// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveToEnemyBTTaskNode.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "WaypointAIController.h"


UMoveToEnemyBTTaskNode::UMoveToEnemyBTTaskNode()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UMoveToEnemyBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::InProgress;
}
void UMoveToEnemyBTTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AWaypointAIController* AIEnemyController = Cast<AWaypointAIController>(OwnerComp.GetOwner());

	EPathFollowingRequestResult::Type MoveToActorResult = AIEnemyController->MoveToEnemy();

	if (MoveToActorResult == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

FString UMoveToEnemyBTTaskNode::GetStaticDescription() const
{
	return TEXT("Persigue al personaje principal");
}