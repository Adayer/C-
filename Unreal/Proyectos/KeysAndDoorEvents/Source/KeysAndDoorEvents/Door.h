// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KeysAndDoorEventsGameModeBase.h"
#include "Kismet/GameplayStatics.h"

#include "Door.generated.h"

UCLASS()
class KEYSANDDOOREVENTS_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
		bool IsOpen;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Door")
		AKeysAndDoorEventsGameModeBase* EventSender;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnKeyPickUp();
};
