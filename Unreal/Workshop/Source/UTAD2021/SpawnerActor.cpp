// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerActor.h"
#include "Engine/DocumentationActor.h"
#include <Runtime/Engine/Public/DrawDebugHelpers.h>

// Sets default values
ASpawnerActor::ASpawnerActor()
  : offset(FVector(0.f, 0.f, 100.f))
	, SpawnedActor(nullptr)
{
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnerActor::BeginPlay()
{
  Super::BeginPlay();

}

void ASpawnerActor::SpawnActor()
{
	FTransform spawnedTransform = offset * GetTransform();
	SpawnedActor = GetWorld()->SpawnActor<AActor>(ClassToSpawn, spawnedTransform);
	OnActorSpawned(true);
}

void ASpawnerActor::UnspawnActor()
{
	if (SpawnedActor)
	{
		SpawnedActor->Destroy();
		SpawnedActor = nullptr;
		OnActorSpawned(false);
	}
}


#if WITH_EDITOR
void ASpawnerActor::PostEditChangeProperty(FPropertyChangedEvent& Event)
{
	Super::PostEditChangeProperty(Event);

	if (Event.GetPropertyName() == GET_MEMBER_NAME_CHECKED(ASpawnerActor, ClassToSpawn))
	{
		ArrowColor = ClassToSpawn.Get() == nullptr ? FColor::Red : FColor::Orange;
	}
}
#endif

// Called every frame
void ASpawnerActor::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

#if WITH_EDITOR	
  if (IsSelectedInEditor())
  {
	  FTransform transform = GetTransform();
	  FVector startPos = transform.GetTranslation();
	  FTransform spawnedTransform = offset * transform;
	  FVector endPos = spawnedTransform.GetTranslation();

	  DrawDebugDirectionalArrow(GetWorld(), startPos, endPos, 100.f, ArrowColor);
  }
#endif
}

