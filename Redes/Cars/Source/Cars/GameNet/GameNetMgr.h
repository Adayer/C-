// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Net/Manager.h"

class UCarsGameInstance;
class CGameNetMgr : public Net::CManager::IObserver
{
public:
	CGameNetMgr();
	CGameNetMgr(UCarsGameInstance* _pOwner);
	virtual ~CGameNetMgr();

	//IObserver
	virtual void dataPacketReceived(Net::CPacket* packet) override;
	virtual void connectionPacketReceived(Net::CPacket* packet) override;
	virtual void disconnectionPacketReceived(Net::CPacket* packet) override;

private:
	Net::CManager* m_pManager = nullptr;
	UCarsGameInstance* m_pCarsGameInstance = nullptr;
};
