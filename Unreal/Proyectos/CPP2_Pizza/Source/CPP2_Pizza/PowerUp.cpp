#include "PowerUp.h"

// Sets default values
APowerUp::APowerUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SphereTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("SphereTrigger"));
	SetRootComponent(SphereTrigger);
}

// Called when the game starts or when spawned
void APowerUp::BeginPlay()
{
	Super::BeginPlay();

	SphereTrigger->SetSphereRadius(20.f);
}

// Called every frame
void APowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator Rotation = GetActorRotation();

	FVector EulerAngles = Rotation.Euler();
	EulerAngles.X += (180.f * DeltaTime);
	EulerAngles.Y += (180.f * DeltaTime);
	EulerAngles.Z += (180.f * DeltaTime);

	FRotator RotationChanged;
	RotationChanged.MakeFromEuler(EulerAngles);

	SetActorRotation(Rotation);
}