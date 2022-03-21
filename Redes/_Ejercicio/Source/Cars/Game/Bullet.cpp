// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Bullet.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameNet/BulletNetComponent.h"
#include "Car.h"


// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	m_pMesh = CreateDefaultSubobject<UStaticMeshComponent>("StatisMesh");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxVisualAsset(TEXT("/Engine/BasicShapes/Sphere"));
	if (BoxVisualAsset.Succeeded())
	{
		m_pMesh->SetStaticMesh(BoxVisualAsset.Object);
		static ConstructorHelpers::FObjectFinder<UMaterial> CarMaterial(TEXT("Material'/Game/Textures/Mat_Red'"));
		m_pMesh->SetMaterial(0, CarMaterial.Object);
	}
	SetRootComponent(m_pMesh);
	SetActorScale3D(FVector(0.1f, 0.1f, 0.1f));
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBulletBeginOverlap);

	m_pNetComponent = CreateDefaultSubobject<UBulletNetComponent>("NetComponent");
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Bullet Movement
	FVector vOffset = (GetActorForwardVector() * m_fSpeed * DeltaTime);
	FVector vNewPos =  GetActorLocation() + vOffset;
	SetActorLocation(vNewPos);
}

void ABullet::OnBulletBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACar* pCar = Cast<ACar>(Other);
	if (pCar)
	{
		m_pNetComponent->ProcessOnBulletBeginOverlap(pCar);
	}
}