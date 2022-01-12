// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Curves/CurveFloat.h"
#include "PowerUp.generated.h"

UCLASS()
class CPP2_PIZZA_API APowerUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerUp();

	//Properties

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USphereComponent* SphereTrigger;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RotationSpeed = 180.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TranslationSpeed = 0.f;
	UPROPERTY(EditAnywhere)
		float Amplitud = 0.f;
	UPROPERTY(EditAnywhere)
		UCurveFloat* Curve;

	UPROPERTY(VisibleAnywhere, Category="Pizza")
		int PorcionesComidas = 0;

private:
	float ElapsedTime = 0.f;
	float InitialZ = 0.f;




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Damage")
		void PickupPowerUp();
	UFUNCTION(BlueprintImplementableEvent, Category = Damage)
		void OnPickupPowerUpDoneEvent();
};
