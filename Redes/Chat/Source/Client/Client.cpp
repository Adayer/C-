// Client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Net/factoryenet.h"
#include "Net/buffer.h"
#include <map>

namespace
{
	const int s_iPort = 65785;
	
	enum class EMessageType
	{
		SetID,
		SetName,
		Message
	};
}


int main()
{
	Net::CFactory* pFactory = new Net::CFactoryEnet();
	Net::CClient* pClient = pFactory->buildClient();
	Net::NetID m_xID = -1;
	std::map<Net::NetID, char*> m_tIDName;
	pClient->init(1);

	std::cout << "Please write the server IP: ";
	char sMessage[128];
	fgets(sMessage, 127, stdin);
	char* sEndLine = strchr(sMessage, '\n');
	(*sEndLine) = '\0';
	Net::CConnection* pConnection = pClient->connect(sMessage, s_iPort, 0);

	std::vector<Net::CPacket*> aPackets;

	bool bIDSet = false;
	do
	{
		pClient->service(aPackets);
		for (std::vector<Net::CPacket*>::iterator it = aPackets.begin(); it != aPackets.end(); ++it)
		{
			Net::CPacket* pPacket = *it;
			Net::CBuffer oData;
			oData.write(pPacket->getData(), pPacket->getDataLength());
			oData.reset();
			EMessageType eMessageType;
			oData.read(&eMessageType,sizeof(eMessageType));
			if (eMessageType == EMessageType::SetID)
			{
				oData.read(&m_xID,sizeof(m_xID));
				bIDSet = true;
			}
			delete pPacket;
		}
		aPackets.clear();



	} while (!bIDSet);

	std::cout << "Please type your name: ";
	fgets(sMessage, 127, stdin);
	sEndLine = strchr(sMessage, '\n');
	(*sEndLine) = '\0';

	Net::CBuffer oData;
	EMessageType eMessageType = EMessageType::SetName;
	oData.write(&eMessageType, sizeof(eMessageType));
	oData.write(&m_xID, sizeof(m_xID));
	oData.write(sMessage, strlen(sMessage));

	pClient->sendData(pConnection, oData.getData(), oData.getSize(), 0, true);
	

	std::cout << "\nConversation Started!\n";
	do
	{
		pClient->service(aPackets);

		for (std::vector<Net::CPacket*>::iterator it = aPackets.begin(); it != aPackets.end(); ++it)
		{
			Net::CPacket* pPacket = *it;

			switch (pPacket->getType())
			{
			case Net::CONNECTION:
			{
				std::cout << "A new foe has joined the frey\n";
			}break;
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
				oData.read(sMessage, iMessageLen);
				sMessage[iMessageLen] = '\0';
				switch (eMessageType)
				{
				case EMessageType::SetName:
				{
					size_t iCopySize = strlen(sMessage) + 1;
					char* sCopy = (char*)malloc(iCopySize);
					strcpy_s(sCopy, iCopySize, sMessage);
					m_tIDName[xID] = sCopy;
					std::cout << sMessage << " has joined.\n";
				}break;
				case EMessageType::Message:
				{
					std::cout << m_tIDName.at(xID) << ": " << sMessage << "\n";
				}break;
				}
			}break;
			case Net::DISCONNECTION:
			{
				std::cout << "A enemy has being slain\n";
			}break;
			}
			delete pPacket;
		}
		aPackets.clear();

		fgets(sMessage, 127, stdin);
		sEndLine = strchr(sMessage, '\n');
		(*sEndLine) = '\0';
		Net::CBuffer oData;
		eMessageType = EMessageType::Message;
		oData.write(&eMessageType, sizeof(eMessageType));
		oData.write(&m_xID, sizeof(m_xID));
		oData.write(sMessage, strlen(sMessage));

		pClient->sendData(pConnection, oData.getData(), oData.getSize(), 0, true);

	} while (strcmp(sMessage, "Exit") != 0);

	pClient->release();

	delete pClient;
	delete pFactory;
}