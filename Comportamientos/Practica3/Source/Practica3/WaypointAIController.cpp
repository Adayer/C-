// Fill out your copyright notice in the Description page of Project Settings.


#include "WaypointAIController.h"
#include "Waypoint.h"
#include "EngineUtils.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void AWaypointAIController::UpdateNextTargetPoint()
{
	UBlackboardComponent* BlackboardComp = BrainComponent->GetBlackboardComponent();
	
	int32 TargetPointIndex = BlackboardComp->GetValueAsInt("TargetPointIndex ");
	
	TargetPointIndex = (++TargetPointIndex) % 4;

	for (TActorIterator<AWaypoint> It(GetWorld()); It; ++It)
	{
		AWaypoint* waypoint = *It;
		if (waypoint->m_iPosition == TargetPointIndex)
		{
			BlackboardComp->SetValueAsVector("TargetPointIndex ", waypoint->GetActorLocation());
			break;
		}
	}
	
	BlackboardComp->SetValueAsInt("TargetPointIndex ", TargetPointIndex);
}