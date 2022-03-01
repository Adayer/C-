// Client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Net/factoryenet.h"
#include "Net/buffer.h"

namespace
{
	const int s_iPort = 65785;
}


int main()
{
	Net::CFactory* pFactory = new Net::CFactoryEnet();
	Net::CClient* pClient = pFactory->buildClient();
	pClient->init(1);

	std::cout << "Please write the server IP: ";
	char sIP[128];
	fgets(sIP, 127, stdin);
	char* sEndLine = strchr(sIP, '\n');
	(*sEndLine) = '\0';
	Net::CConnection* pConnection = pClient->connect(sIP, s_iPort, 0);

	char sMessage[1024];

	std::cout << "Conversation Started!\n";
	std::vector<Net::CPacket*> aPackets;

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

				break;
			}
			case Net::DATA:
			{
				Net::CBuffer oData;
				oData.write(pPacket->getData(), pPacket->getDataLength());
				oData.reset();
				oData.read(sMessage, oData.getSize());
				sMessage[oData.getSize()] = '\0';
				std::cout << sMessage << "\n";

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

		fgets(sMessage, 1023, stdin);
		char* sEndLine = strchr(sIP, '\n');
		(*sEndLine) = '\0';
		//Net::CPacket oMessagePacket(Net::EPacketType::DATA, sMessage, strlen(sMessage), pConnection, 0u);

		pClient->sendData(pConnection, sMessage, strlen(sMessage), 0, true);

	} while (strcmp(sMessage, "Exit") != 0);

	//pClient->disconnect(pConnection);
	pClient->release();

	delete pClient;
	delete pFactory;
}