// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"

#include "Curves/CurveFloat.h"

#include "OscilateComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCPP_API UOscilateComponent : public USceneComponent
{
	GENERATED_BODY()

public:	

	UPROPERTY(EditAnywhere)
		float Amplitud;
	
	UPROPERTY(EditAnywhere)
		UCurveFloat* Curve;


	float ElapsedTime;
	float InitialZ;

	// Sets default values for this component's properties
	UOscilateComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
