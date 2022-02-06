// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "AIControllerPerception.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICA4_API AAIControllerPerception : public AAIController
{
	GENERATED_BODY()
private:

public:
	AAIControllerPerception();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Senses")
		UAIPerceptionComponent* PerceptionCmp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Senses")
		UAISenseConfig_Sight* SightSense;
public:
	UFUNCTION(BlueprintNativeEvent, Category = "Senses")
		void PerceptionUpdated(const TArray<AActor*>& UpdatedActors);

};
