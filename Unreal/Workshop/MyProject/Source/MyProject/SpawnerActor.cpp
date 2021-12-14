// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerActor.h"
#include "Engine/DocumentationActor.h"
#include <Runtime/Engine/Public/DrawDebugHelpers.h>

// Sets default values
ASpawnerActor::ASpawnerActor()
  : offset(FVector(0.f, 0.f, 100.f)),
	m_arrowColor(FColor::Red), 
	spawnedActor(nullptr)
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
	spawnedActor = GetWorld()->SpawnActor<AActor>(classToSpawn, spawnedTransform);
	OnActorSpawnChanged(true);
}

void ASpawnerActor::DestroySpawnedActor()
{
	if (spawnedActor)
	{
		OnActorSpawnChanged(false);
		spawnedActor->Destroy();
		spawnedActor = nullptr;
	}
}

// Called every frame
void ASpawnerActor::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

#if WITH_EDITOR
  if (IsSelectedInEditor())
  {
	  FVector startPos(GetTransform().GetLocation());
	  FVector endPos(GetTransform().GetLocation() + offset.GetLocation());

	  DrawDebugDirectionalArrow(GetWorld(), startPos, endPos, 10.f, m_arrowColor);
  }
#endif

}

#if WITH_EDITOR
void ASpawnerActor::PostEditChangeProperty(FPropertyChangedEvent &_event)
{
	Super::PostEditChangeProperty(_event);

	if (_event.GetPropertyName() == GET_MEMBER_NAME_CHECKED(ASpawnerActor, classToSpawn))
	{
		m_arrowColor = classToSpawn.Get() == nullptr ? FColor::Red : FColor::Yellow;
	}
}
#endif