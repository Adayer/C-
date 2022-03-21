// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BulletNetComponent.generated.h"


namespace Net
{
	class CManager;
}
class CGameBuffer;
class ACar;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CARS_API UBulletNetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBulletNetComponent();
	UFUNCTION()
		void DestroyOwnerActor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	void SerializeData();
	void DeserializeData(CGameBuffer* pData);

public:	
	// Called every frame
	void SetID(unsigned int _uID) { m_uID = _uID; }
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ProcessOnBulletBeginOverlap(ACar* _pOtherCar);

private:
	Net::CManager* m_pManager;
	unsigned int m_uID;
	float m_fBulletLifeTime = 5.f;
};
