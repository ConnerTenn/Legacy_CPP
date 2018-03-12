
#include <iostream>
#include <string>
#include <ws2tcpip.h>
#include <winsock2.h>
#include <windows.h>
#include <iphlpapi.h>

#pragma comment(lib, "Ws2_32.lib")

//SOCKET ConnectionSocket;
//struct addrinfo *server, client;
//uint8_t SendBuffer[2];
//char* port = "666";
//char* ip = "192.168.42.1";

/*
void NetInit()
{
	WSAStartup(MAKEWORD(2, 2), &Wsdata);
	//printw("SYSTEM::Connecting...");
	//refresh();

	client.ai_family = AF_INET;
	client.ai_socktype = SOCK_STREAM;
	client.ai_protocol = IPPROTO_TCP;

	getaddrinfo(ip, port, &client, &server);

	ConnectionSocket = socket(server->ai_family, server->ai_socktype, server->ai_protocol);

	if (connect(ConnectionSocket, server->ai_addr, server->ai_addrlen) == SOCKET_ERROR)
	{
		//printw("ERROR:: Error Connecting to address.\n");
		//refresh();
		WSACleanup();
		exit(0);
	}
}
*/

/*
#define DEFAULT_PORT "27015"
#define IP "192.168.0.162"
#define DEFAULT_BUFLEN 512


WSADATA Wsdata;
struct addrinfo *result = NULL, hints;
SOCKET ListenSocket = INVALID_SOCKET;
SOCKET ClientSocket = INVALID_SOCKET;

void main()
{
	int iResult;

	iResult = WSAStartup(MAKEWORD(2, 2), &Wsdata); if (iResult != 0) { std::cout << "WSAStartup failed: " << iResult << "\n"; return; }

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the local address and port to be used by the server
	iResult = getaddrinfo(IP, DEFAULT_PORT, &hints, &result);	if (iResult != 0) { std::cout << "getaddrinfo failed: " << iResult << "\n"; WSACleanup(); return; }

	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol); if (ListenSocket == INVALID_SOCKET)	{ std::cout << "Error at socket(): " << WSAGetLastError() << "\n"; freeaddrinfo(result); WSACleanup(); return; }

	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);	if (iResult == SOCKET_ERROR) { std::cout << "bind failed with error: " << WSAGetLastError() << "\n"; freeaddrinfo(result); closesocket(ListenSocket); WSACleanup();	return; }

	freeaddrinfo(result);

	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		printf("Listen failed with error: %ld\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return;
	}

	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET)
	{
		printf("accept failed: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return;
	}

	char recvbuf[DEFAULT_BUFLEN];
	int iSendResult;
	int recvbuflen = DEFAULT_BUFLEN;

	// Receive until the peer shuts down the connection
	do
	{
		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
		{
			std::cout << "Bytes received: " << iResult << "\n";

			// Echo the buffer back to the sender
			iSendResult = send(ClientSocket, recvbuf, iResult, 0);
			if (iSendResult == SOCKET_ERROR)
			{
				std::cout << "send failed: " << WSAGetLastError() << "\n";
				closesocket(ClientSocket);
				WSACleanup();
				return;
			}
			std::cout << "Bytes sent: " << iSendResult << "\n";
		}
		else if (iResult == 0)
		{
			std::cout << "Connection closing...\n";
		}
		else
		{
			std::cout << "recv failed: " << WSAGetLastError() << "\n";
			closesocket(ClientSocket);
			WSACleanup();
			return;
		}

	}
	while (iResult > 0);


	// shutdown the send half of the connection since no more data will be sent
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) { std::cout << "shutdown failed: " << WSAGetLastError() << "\n"; closesocket(ClientSocket); WSACleanup(); return; }

	// cleanup
	closesocket(ClientSocket);
	WSACleanup();
}
*/


WSADATA Wsdata;
struct addrinfo *result = NULL, hints;
SOCKET ListenSocket = INVALID_SOCKET;
SOCKET ClientSocket = INVALID_SOCKET;

int InitNetwork(char *ip, char *port)
{
	int iResult;

	iResult = WSAStartup(MAKEWORD(2, 2), &Wsdata); if (iResult != 0) { std::cout << "WSAStartup failed: " << iResult << "\n"; return iResult; }

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the local address and port to be used by the server
	iResult = getaddrinfo(ip, port, &hints, &result);	if (iResult != 0) { std::cout << "getaddrinfo failed: " << iResult << "\n"; WSACleanup(); return iResult; }

	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol); if (ListenSocket == INVALID_SOCKET) { std::cout << "Error at socket(): " << WSAGetLastError() << "\n"; freeaddrinfo(result); WSACleanup(); return iResult; }

	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);	if (iResult == SOCKET_ERROR) { std::cout << "bind failed with error: " << WSAGetLastError() << "\n"; freeaddrinfo(result); closesocket(ListenSocket); WSACleanup();	return iResult; }

	freeaddrinfo(result);

	return 1;
}

int Shutdown()
{
	int iResult;

	// shutdown the send half of the connection since no more data will be sent
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) { std::cout << "shutdown failed: " << WSAGetLastError() << "\n"; closesocket(ClientSocket); WSACleanup(); return iResult; }

	// cleanup
	closesocket(ClientSocket);
	WSACleanup();

	return 1;
}


void main()
{
	int iResult;

	iResult = InitNetwork("192.168.0.162", "27015"); if (iResult <= 0) { return; }
	

	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		printf("Listen failed with error: %ld\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return;
	}

	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET)
	{
		printf("accept failed: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return;
	}

	std::string text;
	do
	{
		do { std::getline(std::cin, text); } while (!text.length());
		uint64_t size = text.length();
		char *sizeBuf = (char *)&size;

		iResult = send(ClientSocket, sizeBuf, 8, 0); if (iResult == SOCKET_ERROR) { std::cout << "send failed: " << WSAGetLastError() << "\n"; closesocket(ClientSocket); WSACleanup(); return; }
		std::cout << "Bytes Sent: " << iResult << "\n";

		iResult = send(ClientSocket, text.c_str(), size, 0); if (iResult == SOCKET_ERROR) { std::cout << "send failed: " << WSAGetLastError() << "\n"; closesocket(ClientSocket); WSACleanup(); return; }
		std::cout << "Bytes Sent: " << iResult << "\n";
	}
	while (text != "exit");

	iResult = Shutdown();
}
