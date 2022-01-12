// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "TileStep.h"

#include "TileFanReceiver.generated.h"

UCLASS()
class UNREALCPP_API ATileFanReceiver : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USceneComponent* RootSceneComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* BladeStaticMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* BaseStaticMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tile")
		ATileStep* TileStepSender;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		//UArrowComponent* ArrowComponent;

	// Sets default values for this actor's properties
	ATileFanReceiver();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	bool IsRotating = false;
	float Time = 0.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnTileTriggered(AActor* OtherActor, bool InOut);

};
