// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

class UBulletNetComponent;
UCLASS()
class CARS_API ABullet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABullet();

	UPROPERTY(EditAnywhere);
	UStaticMeshComponent* m_pMesh;
	UPROPERTY(EditAnywhere);
	UBulletNetComponent* m_pNetComponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
		void OnBulletBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float m_fSpeed = 30.f;
	UBulletNetComponent* GetNetComponent() { return m_pNetComponent; }
};
