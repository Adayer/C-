// Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Net/factoryenet.h"
#include "Net/buffer.h"
#include <map>

namespace
{
	const int s_iPort = 65785;
	const int s_iMaxClients = 10;

	enum class EMessageType
	{
		SetID,
		SetName,
		Message
	};
}

int main()
{
	Net::NetID m_xNextID = 0;
	std::map<Net::NetID, char*> m_tIDName;

	Net::CFactory* pFactory = new Net::CFactoryEnet();
	Net::CServer* pServer = pFactory->buildServer();
	pServer->init(s_iPort, s_iMaxClients);
	std::vector<Net::CPacket*> aPackets;

	char sBuffer[128];

	do
	{
		pServer->service(aPackets);
		for (std::vector<Net::CPacket*>::iterator it = aPackets.begin(); it != aPackets.end(); ++it)
		{
			Net::CPacket* pPacket = *it;

			switch (pPacket->getType())
			{
			case Net::CONNECTION:
			{
				std::cout << "A new foe has joined the frey\n";
				EMessageType eType = EMessageType::SetID;
				
				Net::CBuffer oData;
				oData.write(&eType, sizeof(eType));
				++m_xNextID;
				oData.write(&m_xNextID, sizeof(m_xNextID));
				
				Net::CPacket oIDPacket(Net::DATA, (Net::byte*)&oData, oData.getSize(), pPacket->getConnection(), 0);
				pServer->sendData(oIDPacket.getConnection(), oIDPacket.getData(), oIDPacket.getDataLength(), 0, true);

				break;
			}
			case Net::DATA:
			{
				Net::CBuffer oData;
				oData.write(pPacket->getData(), pPacket->getDataLength());
				oData.reset();
				EMessageType eMessageType;
				oData.read(&eMessageType, sizeof(eMessageType));
				Net::NetID xID;
				oData.read(&xID, sizeof(xID));
				size_t iMessageLen = oData.getSize() - sizeof(eMessageType) - sizeof(xID);
				oData.read(sBuffer, iMessageLen);
				sBuffer[iMessageLen] = '\0';
				switch (eMessageType)
				{
				case EMessageType::SetName:
				{
					size_t iCopySize = strlen(sBuffer) + 1;
					char* sCopy = (char*)malloc(iCopySize);
					strcpy_s(sCopy, iCopySize, sBuffer);
					m_tIDName[xID] = sCopy;
					std::cout << sBuffer << " has joined.\n";
					for (auto& rClient : m_tIDName)
					{
						Net::CBuffer oData;
						EMessageType eMessageType = EMessageType::SetName;
						oData.write(&eMessageType, sizeof(eMessageType));
						oData.write(&(rClient.first), sizeof(rClient.first));
						oData.write(&(rClient.second), strlen(rClient.second));
						pServer->sendData(pPacket->getConnection(), oData.getData(), oData.getSize(), 0, true);
					}
				}break;
				case EMessageType::Message:
				{
					std::cout << m_tIDName.at(xID) << ": " << sBuffer << "\n";
				}break;
				}
				pServer->sendAll(pPacket->getData(), pPacket->getDataLength(), 0, true);
				break;
			}
			case Net::DISCONNECTION:
			{
				std::cout << "A enemy has being slain\n";
				break;
			}
			}
			delete pPacket;
		}

		aPackets.clear();

	} while (strcmp(sBuffer, "shutdown") != 0);

	pServer->release();
	
	delete pServer;
	delete pFactory;

	return 0;
}