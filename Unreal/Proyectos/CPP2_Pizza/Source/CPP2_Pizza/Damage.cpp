// Fill out your copyright notice in the Description page of Project Settings.


#include "Damage.h"
#include "CPP2_PizzaCharacter.h"

// Sets default values
ADamage::ADamage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SphereTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("SphereTrigger"));

	SetRootComponent(DefaultRoot);
	SphereTrigger->SetupAttachment(DefaultRoot);
	StaticMesh->SetupAttachment(DefaultRoot);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ADamage::BeginPlay()
{
	Super::BeginPlay();

	SphereTrigger->OnComponentBeginOverlap.AddDynamic(this, &ADamage::TriggerEnter);
}

// Called every frame
void ADamage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADamage::TriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Display, TEXT("Damage Player"));

	ACPP2_PizzaCharacter* otherChar = Cast<ACPP2_PizzaCharacter>(OtherActor);

	if (otherChar)
	{
		otherChar->ModifyEnergy(-2);
	}
}


