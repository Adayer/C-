// Fill out your copyright notice in the Description page of Project Settings.


#include "GameNet/BulletNetComponent.h"
#include "Net/Manager.h"
#include "DrawDebugHelpers.h"
#include "GameNet/GameBuffer.h"
#include "../CarsGameInstance.h"
#include "GameNet/GameNetMgr.h"
#include "../Game/Car.h"
#include "../Game/CarMovementComponent.h"
#include "NetComponent.h"


// Sets default values for this component's properties
UBulletNetComponent::UBulletNetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	m_pManager = Net::CManager::getSingletonPtr();
	// ...
}


// Called when the game starts
void UBulletNetComponent::BeginPlay()
{
	Super::BeginPlay();
	m_fBulletLifeTime = 5.f;
	// ...
	
}


// Called every frame
void UBulletNetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_pManager->getID() == Net::ID::SERVER)
	{
		m_fBulletLifeTime -= DeltaTime;

		if (m_fBulletLifeTime <= 0)
		{
			SerializeData();
			GetOwner()->Destroy();
			Cast<UCarsGameInstance>(GetWorld()->GetGameInstance())->m_oGameNetMgr.DestroyBullet(m_uID);
		}	
	}
	else
	{
		//DeserializeData();
	}
}

void UBulletNetComponent::SerializeData()
{
	CGameBuffer oData;
	Net::NetMessageType eMType = Net::NetMessageType::BULLET_DESTROY;
	oData.write(eMType);
	oData.write(m_uID);
	m_pManager->send(&oData, true);
}

void UBulletNetComponent::DeserializeData(CGameBuffer* pData)
{
	if (m_pManager->getID() == Net::ID::SERVER)
	{
	}
	else
	{
	}
}
void UBulletNetComponent::DestroyOwnerActor()
{
	GetOwner()->Destroy();
	Cast<UCarsGameInstance>(GetWorld()->GetGameInstance())->m_oGameNetMgr.DestroyBullet(m_uID);
}
void UBulletNetComponent::ProcessOnBulletBeginOverlap(ACar* _pOtherCar)
{
	if (m_pManager->getID() == Net::ID::SERVER)
	{
		if (_pOtherCar->GetNetComponent()->GetID() != m_uID)
		{
			//Stop the car
			_pOtherCar->GetCarMovementComponent()->StopCarMovement();
			
			//Send message to stop client car
			CGameBuffer oData;
			Net::NetMessageType eMType = Net::NetMessageType::BULLET_DESTROY;
			oData.write(eMType);
			oData.write(m_uID);
			m_pManager->send(&oData, true);
			
			GetOwner()->Destroy();
			Cast<UCarsGameInstance>(GetWorld()->GetGameInstance())->m_oGameNetMgr.DestroyBullet(m_uID);
		}
	}
}
//void UBulletNetComponent::DestroyBulletFromServer()
//{
//	SerializeData();
//	GetOwner()->Destroy();
//}