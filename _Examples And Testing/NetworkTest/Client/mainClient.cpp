
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
struct addrinfo *result = NULL, *ptr = NULL, hints;
SOCKET ConnectSocket = INVALID_SOCKET;

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
	iResult = getaddrinfo(IP, DEFAULT_PORT, &hints, &result); if (iResult != 0) { std::cout << "getaddrinfo failed: " << iResult << "\n"; WSACleanup(); return; }

	ptr = result;

	// Create a SOCKET for connecting to server
	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

	if (ConnectSocket == INVALID_SOCKET) { std::cout << "Error at socket(): " << WSAGetLastError() << "\n"; freeaddrinfo(result); WSACleanup(); return; }

	// Connect to server.
	iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen); if (iResult == SOCKET_ERROR) { closesocket(ConnectSocket); ConnectSocket = INVALID_SOCKET; }

	// Should really try the next address returned by getaddrinfo
	// if the connect call failed
	// But for this simple example we just free the resources
	// returned by getaddrinfo and print an error message

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) { std::cout << "Unable to connect to server!\n"; WSACleanup(); return; }






	int recvbuflen = DEFAULT_BUFLEN;

	char *sendbuf = "this is a test";
	char recvbuf[DEFAULT_BUFLEN];

	// Send an initial buffer
	iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0); if (iResult == SOCKET_ERROR) { std::cout << "send failed: " <<  WSAGetLastError() << "\n"; closesocket(ConnectSocket); WSACleanup(); return; }

	std::cout << "Bytes Sent: " << iResult << "\n";

	// shutdown the connection for sending since no more data will be sent
	// the client can still use the ConnectSocket for receiving data
	iResult = shutdown(ConnectSocket, SD_SEND);	if (iResult == SOCKET_ERROR) { std::cout << "shutdown failed: " << WSAGetLastError() << "\n"; closesocket(ConnectSocket); WSACleanup(); return; }

	// Receive data until the server closes the connection
	do
	{
		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
		{
			std::cout << "Bytes received: " << iResult << "\n";
		}
		else if (iResult == 0)
		{
			std::cout << "Connection closed\n";
		}
		else
		{
			std::cout << "recv failed: " << WSAGetLastError() << "\n";
		}
	}
	while (iResult > 0);


	// shutdown the send half of the connection since no more data will be sent
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) { std::cout << "shutdown failed: " << WSAGetLastError() << "\n"; closesocket(ConnectSocket); WSACleanup(); return; }

	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();
}

*/


//#define DEFAULT_PORT "27015"
//#define IP "192.168.0.162"
//#define DEFAULT_BUFLEN 512


WSADATA Wsdata;
struct addrinfo *result = NULL, *ptr = NULL, hints;
SOCKET ConnectSocket = INVALID_SOCKET;

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
	iResult = getaddrinfo(ip, port, &hints, &result); if (iResult != 0) { std::cout << "getaddrinfo failed: " << iResult << "\n"; WSACleanup(); return iResult; }

	ptr = result;

	// Create a SOCKET for connecting to server
	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

	if (ConnectSocket == INVALID_SOCKET) { std::cout << "Error at socket(): " << WSAGetLastError() << "\n"; freeaddrinfo(result); WSACleanup(); return iResult; }

	// Connect to server.
	iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen); if (iResult == SOCKET_ERROR) { std::cout << "Socket Error: " << WSAGetLastError() << "\n"; closesocket(ConnectSocket); ConnectSocket = INVALID_SOCKET; return iResult; }

	// Should really try the next address returned by getaddrinfo
	// if the connect call failed
	// But for this simple example we just free the resources
	// returned by getaddrinfo and print an error message

	freeaddrinfo(result);

	return 1;
}

int Shutdown()
{
	int iResult;
	// shutdown the send half of the connection since no more data will be sent
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) { std::cout << "shutdown failed: " << WSAGetLastError() << "\n"; closesocket(ConnectSocket); WSACleanup(); return iResult; }

	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();

	return iResult;
}

void main()
{
	int iResult;

	iResult = InitNetwork("192.168.0.162", "27015"); if (iResult <= 0) { return; }



	// Receive data until the server closes the connection
	char recieveSizeBuf[8];
	char *dataBuf;
	uint64_t size;
	do
	{
		iResult = recv(ConnectSocket, recieveSizeBuf, 8, 0);
		if (iResult > 0) { std::cout << "Bytes received: " << iResult << "\n"; }
		else if (iResult == 0) { std::cout << "Connection closed\n"; return; }
		else { std::cout << "recv failed: " << WSAGetLastError() << "\n"; return; }

		size = *((uint64_t *)recieveSizeBuf);
		dataBuf = new char[size];
		iResult = recv(ConnectSocket, dataBuf, size, 0);
		if (iResult > 0) { std::cout << "Bytes received: " << iResult << "\n"; }
		else if (iResult == 0) { std::cout << "Connection closed\n"; return; }
		else { std::cout << "recv failed: " << WSAGetLastError() << "\n"; return; }

		std::cout << "Received:" << std::string(dataBuf, size) << "\n";

		delete dataBuf;
	}
	while (iResult > 0);

	iResult = Shutdown();
}
