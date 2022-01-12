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

	const FTransform& Transform = GetTransform();
	const FVector& Location = Transform.GetLocation();
	InitialZ = Location.Z;
}

// Called every frame
void APowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator Rotation = GetActorRotation();
	Rotation.Yaw += (RotationSpeed * DeltaTime);
	SetActorRotation(Rotation);


	if (ensure(Curve))
	{
		ElapsedTime += DeltaTime;

		float MaxTime, MinTime;
		Curve->GetTimeRange(MinTime, MaxTime);

		float TimeInRange = fmod(ElapsedTime * TranslationSpeed, MaxTime);
		float Heigth = Curve->GetFloatValue(TimeInRange);

		FVector Location(GetTransform().GetLocation());
		Location.Z = Heigth * Amplitud + InitialZ;

		SetActorLocation(Location);
	}
}

void APowerUp::PickupPowerUp()
{
	++PorcionesComidas;
	UE_LOG(LogTemp, Display, TEXT("Porciones de pizza: %d"), PorcionesComidas);
	OnPickupPowerUpDoneEvent();
}