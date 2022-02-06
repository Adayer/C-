// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllerPerception.h"

AAIControllerPerception::AAIControllerPerception()
{
	PerceptionCmp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));
	SightSense = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));
	PerceptionCmp->ConfigureSense(*SightSense);
	PerceptionCmp->SetDominantSense(SightSense->GetSenseImplementation());

	PerceptionCmp->OnPerceptionUpdated.AddDynamic(this, &AAIControllerPerception::PerceptionUpdated);
}
void AAIControllerPerception::PerceptionUpdated_Implementation(const TArray<AActor*>& UpdatedActors)
{

}