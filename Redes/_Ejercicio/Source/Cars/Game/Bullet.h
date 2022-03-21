// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

class UBulletNetComponent;
class USphereComponent;
UCLASS()
class CARS_API ABullet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABullet();

	UPROPERTY(EditAnywhere);
	USphereComponent* m_pSphereCollision;
	UPROPERTY(EditAnywhere);
	UStaticMeshComponent* m_pMesh;
	UPROPERTY(EditAnywhere);
	UBulletNetComponent* m_pNetComponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
		void OnBulletBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	bool bGeneratingOverlapEvents = false;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float m_fSpeed = 800.f;
	UBulletNetComponent* GetNetComponent() { return m_pNetComponent; }
};
