// Fill out your copyright notice in the Description page of Project Settings.


#include "TileStep.h"

// Sets default values
ATileStep::ATileStep()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger"));

	SetRootComponent(DefaultRoot);
	BoxComponent->SetupAttachment(DefaultRoot);

	StaticMesh->SetupAttachment(DefaultRoot);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ATileStep::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ATileStep::OnStepIn);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ATileStep::OnStepOut);
}

// Called every frame
void ATileStep::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATileStep::OnStepIn(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Display, TEXT("Stepped In"));
	SteppedEvent.Broadcast(OtherActor, true);
}

void ATileStep::OnStepOut(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Display, TEXT("Stepped Out"));
	SteppedEvent.Broadcast(OtherActor, false);
}

