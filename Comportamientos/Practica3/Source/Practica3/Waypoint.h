// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "Waypoint.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICA3_API AWaypoint : public ATargetPoint
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Waypoints")
		int32 m_iPosition;
	
};
