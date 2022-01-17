// Fill out your copyright notice in the Description page of Project Settings.


#include "MyKey.h"

// Sets default values
AMyKey::AMyKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SphereTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("SphereTrigger"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	SetRootComponent(DefaultRoot);
	StaticMesh->SetupAttachment(DefaultRoot);
	SphereTrigger->SetupAttachment(DefaultRoot);
}

// Called when the game starts or when spawned
void AMyKey::BeginPlay()
{
	Super::BeginPlay();

	SphereTrigger->OnComponentBeginOverlap.AddDynamic(this, &AMyKey::Broadcast);
}

// Called every frame
void AMyKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyKey::Broadcast(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}