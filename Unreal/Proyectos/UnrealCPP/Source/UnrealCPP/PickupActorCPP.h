// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "OscilateComponent.h"
#include "PickupActorCPP.generated.h"

UCLASS()
class UNREALCPP_API APickupActorCPP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupActorCPP();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USceneComponent* DefaultRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* StaticMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USphereComponent* SphereTrigger;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UOscilateComponent* OscillateCmp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
