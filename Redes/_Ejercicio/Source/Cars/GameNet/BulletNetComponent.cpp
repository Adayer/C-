// Fill out your copyright notice in the Description page of Project Settings.


#include "GameNet/BulletNetComponent.h"
#include "Net/Manager.h"
#include "DrawDebugHelpers.h"
#include "GameNet/GameBuffer.h"

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
		}
	}
	else
	{
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
