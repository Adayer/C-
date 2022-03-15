// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Net/Manager.h"
#include <map>
/**
 * 
 */
class UCarsGameInstance;
class ACar;
class ABullet;

class CGameNetMgr : public Net::CManager::IObserver
{
public:
	CGameNetMgr();
	CGameNetMgr(UCarsGameInstance* _pOwner);
	~CGameNetMgr();

	virtual void dataPacketReceived(Net::CPacket* packet) override;
	virtual void connectionPacketReceived(Net::CPacket* packet) override;
	virtual void disconnectionPacketReceived(Net::CPacket* packet) override;
	void DestroyBullet(unsigned int _uClient);

private:
	void CreateCar(unsigned int _uClient, FVector _vPos);
	void CreateBullet(unsigned int _uClient);

private:
	Net::CManager* m_pManager = nullptr;
	UCarsGameInstance* m_pCarsGameInstance;
	unsigned int m_uMapLoadedNotifications = 0u;
	std::map<unsigned int, ACar*> m_tPlayers;
	std::map<unsigned int, ABullet*> m_tBullets;
};
