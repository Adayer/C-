// Fill out your copyright notice in the Description page of Project Settings.

#include "GameCamera.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGameCamera::AGameCamera()
{
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGameCamera::BeginPlay()
{
  Super::BeginPlay();
  APlayerController* OurPC = UGameplayStatics::GetPlayerController(this, 0);
  if (OurPC)
  {
    OurPC->SetViewTarget(this);
  }
}

// Called every frame
void AGameCamera::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
}
