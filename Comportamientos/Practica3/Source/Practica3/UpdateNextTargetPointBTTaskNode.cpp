// Fill out your copyright notice in the Description page of Project Settings.


#include "UpdateNextTargetPointBTTaskNode.h"
#include "WaypointAIController.h"

EBTNodeResult::Type UUpdateNextTargetPointBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AWaypointAIController* aiCtrl = Cast<AWaypointAIController>(OwnerComp.GetOwner());
	if (!aiCtrl)
	{
		return EBTNodeResult::Failed;
	}
	aiCtrl->UpdateNextTargetPoint();
	return EBTNodeResult::Succeeded;
}
FString UUpdateNextTargetPointBTTaskNode::GetStaticDescription() const
{
	return TEXT("Actualiza al siguiente punto del recorrido");
}