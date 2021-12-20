// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnerActor.generated.h"

UCLASS()
class UTAD2021_API ASpawnerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool ShouldTickIfViewportsOnly() const override { return true; }

	UFUNCTION(BlueprintCallable)
	void SpawnActor();

	UFUNCTION(BlueprintCallable)
	bool IsActorSpawned() const { return SpawnedActor != nullptr; }

	UFUNCTION(BlueprintCallable)
	void UnspawnActor();

	UFUNCTION(BlueprintImplementableEvent)
	void OnActorSpawned(bool bSpawned);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& Event) override;
#endif

private:
	UPROPERTY(EditAnywhere, Category="Spawner")
	FTransform offset;

	UPROPERTY(EditAnywhere, Category = "Spawner")
		TSubclassOf<AActor> ClassToSpawn;

	FColor ArrowColor;

	AActor* SpawnedActor;
};
