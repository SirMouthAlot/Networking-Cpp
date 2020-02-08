#include "NetworkingWrapper.h"

int NetworkingWrapper::m_maxClients = 4;

SOCKET NetworkingWrapper::m_socket;
struct addrinfo* NetworkingWrapper::m_ptr = NULL, m_hints;
struct addrinfo NetworkingWrapper::m_hints;
struct std::vector<sockaddr_in> NetworkingWrapper::m_addresses;

bool NetworkingWrapper::StartupWinsock()
{
	//Initialize winsock
	WSADATA wsa;

	int error;
	error = WSAStartup(MAKEWORD(2, 2), &wsa);

	if (error != 0) {
		printf("Failed to initialize %d\n", error);
		return false;
	}
	return true;
}

void NetworkingWrapper::SetupHints(int family, int sockType, int protocol, int flag)
{
	memset(&m_hints, 0, sizeof(m_hints));
	m_hints.ai_family = family;
	m_hints.ai_socktype = sockType;
	m_hints.ai_protocol = protocol;
	m_hints.ai_flags = flag;
}

void NetworkingWrapper::ConnectTo(std::string ip)
{
	if (ip == "")
	{
		if (getaddrinfo(NULL, "8888", &m_hints, &m_ptr) != 0) {
			printf("Getaddrinfo failed!! %d\n", WSAGetLastError());
			WSACleanup();
			return;
		}
	}
	else
	{
		if (getaddrinfo(ip.c_str(), "8888", &m_hints, &m_ptr) != 0) {
			printf("Getaddrinfo failed!! %d\n", WSAGetLastError());
			WSACleanup();
			return;
		}
	}
}

void NetworkingWrapper::CreateSocket(IPPROTO protocol)
{
	m_socket = socket(AF_INET, SOCK_DGRAM, protocol);

	if (m_socket == INVALID_SOCKET) {
		printf("Failed creating a socket %d\n", WSAGetLastError());
		WSACleanup();
		return;
	}
}

bool NetworkingWrapper::BindSocket()
{
	if (bind(m_socket, m_ptr->ai_addr, (int)m_ptr->ai_addrlen) == SOCKET_ERROR) {
		printf("Bind failed: %d\n", WSAGetLastError());
		closesocket(m_socket);
		freeaddrinfo(m_ptr);
		WSACleanup();
		return false;
	}

	return true;
}

bool NetworkingWrapper::SendMsg(Convertable* message)
{
	//Make sure there's a conversion between T and string
	std::string converted = message->ToString();

	if (sendto(m_socket, converted.c_str(), (int)converted.size(), 0,
		m_ptr->ai_addr, m_ptr->ai_addrlen) == SOCKET_ERROR)
	{
		printf("Message failed to send!\n");
		return false;
	}

	return true;
}

bool NetworkingWrapper::SendMsg(Convertable* message, sockaddr_in destinationSock)
{
	//Make sure there's a conversion between T and string
	std::string converted = message->ToString();

	if (sendto(m_socket, converted.c_str(), (int)converted.size(), 0,
		(const sockaddr*)&destinationSock, sizeof(destinationSock)) == SOCKET_ERROR)
	{
		printf("Message failed to send!\n");
		return false;
	}

	return true;
}

bool NetworkingWrapper::ReceiveMsg(Convertable* message)
{
	// Receive msg from client
	const unsigned int BUF_LEN = 512;
	char recv_buf[BUF_LEN];

	//!!!!!REMEMBER TO SET MEMORY TO 0s!!!!!//
	memset(recv_buf, 0, BUF_LEN);

	// Struct that will hold the IP address of the client that sent the message (we don't have accept() anymore to learn the address)
	struct sockaddr_in fromAddr;
	int fromlen;
	fromlen = sizeof(fromAddr);

	if (recvfrom(m_socket, recv_buf, sizeof(recv_buf), 0,
		(struct sockaddr*) & fromAddr, &fromlen) == SOCKET_ERROR)
	{
		printf("recvfrom() failed...%d\n", WSAGetLastError());
		return false;
	}

	int clientNum = FindClient(fromAddr);

	if (clientNum == -1)
	{
		//Ignore this mother fucker
		return false;
	}

	printf("Message from Client %i: ", clientNum);

	//Turns recv buffer into a string
	std::string temp;
	temp += recv_buf;
	//Converts the string back into the correct type and stores it in referenced message
	message->SetValue(temp);

	return true;
}


int NetworkingWrapper::FindClient(sockaddr_in clientAddr)
{
	auto it = std::find_if(m_addresses.begin(), m_addresses.end(), SAInCompare(clientAddr));

	if (it == m_addresses.end())
	{
		return AddClient(clientAddr);
	}

	//Returns the position in index
	return (it - m_addresses.begin());
}

int NetworkingWrapper::AddClient(sockaddr_in clientAddr)
{
	if (m_addresses.size() <= m_maxClients)
	{
		m_addresses.push_back(clientAddr);
		return m_addresses.size() - 1;
	}

	return -1;
}

int NetworkingWrapper::GetNumConnected()
{
	return m_addresses.size();
}

bool NetworkingWrapper::ShutdownSocket()
{
	//Shutdown the socket
	if (shutdown(m_socket, SD_BOTH) == SOCKET_ERROR) {
		printf("Shutdown failed!  %d\n", WSAGetLastError());
		closesocket(m_socket);
		WSACleanup();
		return false;
	}

	CloseWinsock();
	
	return true;
}


void NetworkingWrapper::CloseWinsock()
{
	closesocket(m_socket);
	freeaddrinfo(m_ptr);
	WSACleanup();
}
