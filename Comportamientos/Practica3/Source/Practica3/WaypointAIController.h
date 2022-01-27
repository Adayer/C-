// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WaypointAIController.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICA3_API AWaypointAIController : public AAIController
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Waypoints")
		void UpdateNextTargetPoint();
};
