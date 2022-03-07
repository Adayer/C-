// Fill out your copyright notice in the Description page of Project Settings.


#include "GameNet/GameNetMgr.h"
#include "../CarsGameInstance.h"
//#include "Net/buffer.h"
#include "GameNet/GameBuffer.h"
#include "Net/packet.h"

CGameNetMgr::CGameNetMgr()
{
	Net::CManager::Init();
	m_pManager = Net::CManager::getSingletonPtr();
	m_pManager->addObserver(this);
}

CGameNetMgr::CGameNetMgr(UCarsGameInstance* _pOwner) :
	m_pCarsGameInstance(_pOwner)
{
	Net::CManager::Init();
	m_pManager = Net::CManager::getSingletonPtr();
	m_pManager->addObserver(this);
}

CGameNetMgr::~CGameNetMgr()
{
	m_pManager->removeObserver(this);
	Net::CManager::Release();
	m_pManager = nullptr;
	m_pCarsGameInstance = nullptr;
}


void CGameNetMgr::dataPacketReceived(Net::CPacket* packet)
{
	if (m_pManager->getID() == Net::ID::SERVER)
	{

	}
	else
	{
		Net::CBuffer oData;
		oData.write(packet->getData(), packet->getDataLength());
		oData.reset();
		char sInfo[32];
		oData.read(sInfo);

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, sInfo);
	}
}
void CGameNetMgr::connectionPacketReceived(Net::CPacket* packet)
{
	if (m_pManager->getID() == Net::ID::SERVER)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, "SOME FUCKING NOBODY CONNECTED!");

		Net::CBuffer oData;
		const char* sHello = "Connected";
		oData.write(sHello);
		m_pManager->send(&oData, true);
	}
}
void CGameNetMgr::disconnectionPacketReceived(Net::CPacket* packet)
{

}