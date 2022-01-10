// Fill out your copyright notice in the Description page of Project Settings.


#include "OscilateComponent.h"

// Sets default values for this component's properties
UOscilateComponent::UOscilateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOscilateComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	const FTransform& Transform = GetRelativeTransform();
	const FVector& Location = Transform.GetLocation();
	InitialZ = Location.Z;
}


// Called every frame
void UOscilateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	ElapsedTime += DeltaTime;

	if (ensure(Curve))
	{
		float MaxTime, MinTime;
		Curve->GetTimeRange(MinTime, MaxTime);

		float TimeInRange = fmod(ElapsedTime, MaxTime);
		float Heigth = Curve->GetFloatValue(TimeInRange);

		FVector Location(GetRelativeTransform().GetLocation());
		Location.Z = Heigth * Amplitud + InitialZ;

		SetRelativeLocation(Location);

		UE_LOG(LogTemp, Display, TEXT("Relative Location %0.3f %0.3f %0.3f") , Location.X, Location.Y, Location.Z)
	}
}

