// Fill out your copyright notice in the Description page of Project Settings.

#include "CarsGameModeBase.h"
#include "Game/CarsPlayerController.h"

ACarsGameModeBase::ACarsGameModeBase(const class FObjectInitializer& ObjectInitializer) : AGameModeBase(ObjectInitializer)
{
  PlayerControllerClass = ACarsPlayerController::StaticClass();
}

APawn* ACarsGameModeBase::SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot)
{
  return nullptr;
}


