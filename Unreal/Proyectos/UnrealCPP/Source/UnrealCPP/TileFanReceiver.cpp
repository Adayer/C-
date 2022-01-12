// Fill out your copyright notice in the Description page of Project Settings.


#include "TileFanReceiver.h"

// Sets default values
ATileFanReceiver::ATileFanReceiver()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	BaseStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseStaticMesh"));
	BladeStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BladeStaticMesh"));

	SetRootComponent(RootSceneComponent);
	BaseStaticMesh->SetupAttachment(RootSceneComponent);
	BladeStaticMesh->SetupAttachment(RootSceneComponent);
}

// Called when the game starts or when spawned
void ATileFanReceiver::BeginPlay()
{
	Super::BeginPlay();
	if (TileStepSender)
	{
		TileStepSender->SteppedEvent.AddDynamic(this, &ATileFanReceiver::OnTileTriggered);
	}
}

// Called every frame
void ATileFanReceiver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsRotating)
	{
		Time += DeltaTime;
		Time = Time > 1 ? 0 : Time;
		FRotator Rotation;
		float Speed = 3.f;
		Rotation.Roll = Speed * Time * 360.f;
		BladeStaticMesh->SetRelativeRotation(Rotation);

		UE_LOG(LogTemp, Warning, TEXT("Rotating: %0.3f\n"), Rotation.Roll);
	}
}

void ATileFanReceiver::OnTileTriggered(AActor* OtherActor, bool InOut)
{
	IsRotating = InOut;
}