// Client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

int main()
{
	WSADATA xWsa;
	WSAStartup(MAKEWORD(2, 2), &xWsa);

	SOCKET xSocket;
	xSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (xSocket == -1)
	{
		std::cout << "SOCKET INITIALIZATION ERROR!\n";
		return -1;
	}

	struct sockaddr_in xSockAddr;
	xSockAddr.sin_family = AF_INET;
	xSockAddr.sin_port = htons(9999);
	inet_pton(AF_INET, "127.0.0.1", &xSockAddr.sin_addr);
	memset(xSockAddr.sin_zero, 0, 8);

	int iConnection = connect(xSocket, (sockaddr*)&xSockAddr, sizeof(xSockAddr));
	if (iConnection == -1)
	{
		std::cout << "CONNECTION FAILED\n";
		return -1;
	}

	char sBuffer[1024];
	int iLen = 0;

	do
	{
		std::cout << "Type a message: ";
		//std::cin >> sBuffer;
		fgets(sBuffer, 1023, stdin); //Este lee espacios e intros
		iLen = send(xSocket, sBuffer, strlen(sBuffer), 0);

	} while (iLen != -1 && strcmp(sBuffer, "Exit\n") != 0);

	closesocket(xSocket);
	return 0;
}