// Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Net/factoryenet.h"
#include "Net/buffer.h"

namespace
{
	const int s_iPort = 65785;
	const int s_iMaxClients = 10;
}

int main()
{
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

				break;
			}
			case Net::DATA:
			{
				Net::CBuffer oData;
				oData.write(pPacket->getData(), pPacket->getDataLength());
				oData.reset();
				oData.read(sBuffer, oData.getSize());
				sBuffer[oData.getSize()] = '\0';
				std::cout << sBuffer << "\n";
				pServer->sendAll(sBuffer, strlen(sBuffer), 0, true);

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