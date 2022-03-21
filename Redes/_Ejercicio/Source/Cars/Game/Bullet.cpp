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
	
	m_pSphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	m_pSphereCollision->SetGenerateOverlapEvents(false);
	RootComponent = m_pSphereCollision;
	SetRootComponent(m_pSphereCollision);
	m_pMesh = CreateDefaultSubobject<UStaticMeshComponent>("StatisMesh");
	m_pMesh->SetGenerateOverlapEvents(false);
	m_pMesh->SetupAttachment(m_pSphereCollision);
	m_pMesh->SetRelativeLocation(FVector::ZeroVector);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxVisualAsset(TEXT("/Engine/BasicShapes/Sphere"));
	if (BoxVisualAsset.Succeeded())
	{
		m_pMesh->SetStaticMesh(BoxVisualAsset.Object);
		static ConstructorHelpers::FObjectFinder<UMaterial> CarMaterial(TEXT("Material'/Game/Textures/Mat_Red'"));
		m_pMesh->SetMaterial(0, CarMaterial.Object);
	}
	m_pSphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBulletBeginOverlap);
	m_pNetComponent = CreateDefaultSubobject<UBulletNetComponent>("NetComponent");
	SetActorScale3D(FVector(.1f, .1f, .1f));
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	bGeneratingOverlapEvents = false;
	m_pSphereCollision->SetGenerateOverlapEvents(false);
	m_pMesh->SetGenerateOverlapEvents(false);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bGeneratingOverlapEvents)
	{
		bGeneratingOverlapEvents = true;
		m_pSphereCollision->SetGenerateOverlapEvents(true);
		m_pMesh->SetGenerateOverlapEvents(true);
	}

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