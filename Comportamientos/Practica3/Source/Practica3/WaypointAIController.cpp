// Fill out your copyright notice in the Description page of Project Settings.


#include "WaypointAIController.h"
#include "Waypoint.h"
#include "EngineUtils.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Practica3Character.h"

void AWaypointAIController::UpdateNextTargetPoint()
{
	UBlackboardComponent* BlackboardComp = BrainComponent->GetBlackboardComponent();
	
	int32 TargetPointIndex = BlackboardComp->GetValueAsInt("TargetPointIndex");
	
	TargetPointIndex = (++TargetPointIndex) % 4;

	for (TActorIterator<AWaypoint> It(GetWorld()); It; ++It)
	{
		AWaypoint* waypoint = *It;
		if (waypoint->m_iPosition == TargetPointIndex)
		{
			BlackboardComp->SetValueAsVector("TargetPointPosition", waypoint->GetActorLocation());
			break;
		}
	}
	
	BlackboardComp->SetValueAsInt("TargetPointIndex", TargetPointIndex);
}

void AWaypointAIController::CheckNearbyEnemy()
{
	APawn* thisPawn = GetPawn();
	FVector sphereTraceStart = thisPawn->GetActorLocation();
	FVector sphereTraceEnd(sphereTraceStart.X, sphereTraceStart.Y, sphereTraceStart.Z + 15.f);
	float Radius = 1500.f;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	TArray<AActor*> ActorsToIgnore; 
	ActorsToIgnore.Add(thisPawn);

	TArray<FHitResult> OutHits;

	bool ResultOfTrace = 
		UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), 
			sphereTraceStart, 
			sphereTraceEnd, 
			Radius,
			ObjectTypes, 
			false,
			ActorsToIgnore,
			EDrawDebugTrace::ForDuration,
			OutHits,
			true);
	//TODO: Put value in bb and check if player has been hit

	if (ResultOfTrace)
	{
		for (int32 i = 0; i < OutHits.Num(); ++i)
		{
			FHitResult HitInfo = OutHits[i];

			if (Cast<APractica3Character>(HitInfo.GetActor()))
			{
				Blackboard->SetValueAsObject("TargetToFollow", HitInfo.GetActor());
				break;
			}
		}
	}
	else
	{
		Blackboard->SetValueAsObject("TargetToFollow", NULL);
	}
}