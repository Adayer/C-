// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupActorCPP.h"

// Sets default values
APickupActorCPP::APickupActorCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SphereTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("SphereTrigger"));
	OscillateCmp = CreateDefaultSubobject<UOscilateComponent>(TEXT("OscillateCmp"));

	SetRootComponent(DefaultRoot);
	SphereTrigger->SetupAttachment(DefaultRoot);
	OscillateCmp->SetupAttachment(DefaultRoot);
	StaticMesh->SetupAttachment(OscillateCmp);
}

// Called when the game starts or when spawned
void APickupActorCPP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupActorCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

