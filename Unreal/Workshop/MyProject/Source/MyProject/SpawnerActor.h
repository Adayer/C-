// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnerActor.generated.h"

UCLASS()
class MYPROJECT_API ASpawnerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnerActor(); 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	AActor* spawnedActor = nullptr;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SpawnActor();

	UFUNCTION(BlueprintCallable)
	void DestroySpawnedActor();

	UFUNCTION(BlueprintCallable)
	bool GetIfActorSpawned() const { return (spawnedActor != nullptr); }

	UFUNCTION(BlueprintImplementableEvent)
	bool OnActorSpawnChanged();

private:
	UPROPERTY(EditAnywhere, Category="Spawner")
	FTransform offset;

	UPROPERTY(EditAnywhere, Category="Spawner")
	TSubclassOf<AActor> classToSpawn;



	FColor m_arrowColor;
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent &_event) override;
#endif


	bool ShouldTickIfViewportsOnly() const override {return true;}
};
