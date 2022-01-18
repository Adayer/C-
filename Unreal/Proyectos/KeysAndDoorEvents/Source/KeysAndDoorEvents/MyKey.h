// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Delegates/DelegateCombinations.h"
#include "MyKey.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FKeyPickUpSignature);


UCLASS()
class KEYSANDDOOREVENTS_API AMyKey : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyKey();
	
	UPROPERTY()
		USceneComponent* DefaultRoot;
	UPROPERTY()
		USphereComponent* SphereTrigger;
	UPROPERTY()
		UStaticMeshComponent* StaticMesh;
	UPROPERTY(BlueprintAssignable, Category = "Key")
		FKeyPickUpSignature PickUpEvent;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnPickUp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
