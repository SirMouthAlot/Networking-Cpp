#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

#include "Number.h"
#include "String.h"

#pragma comment(lib, "Ws2_32.lib")

struct SAInCompare
{
public:
	SAInCompare(const sockaddr_in& original) : m_original(original) { }

	bool operator()(const sockaddr_in& compare) const
	{
		bool addressSame = (m_original.sin_addr.S_un.S_addr == compare.sin_addr.S_un.S_addr);
		bool familySame = m_original.sin_family == compare.sin_family;
		bool portSame = m_original.sin_port == compare.sin_port;
		bool zeroSame = m_original.sin_zero == compare.sin_zero;

		return (addressSame && familySame && portSame && zeroSame);
	}

	sockaddr_in m_original;
};

class NetworkingWrapper abstract
{
public:
	static bool StartupWinsock();
	static void SetupHints(int family = AF_INET, int sockType = SOCK_DGRAM, int protocol = IPPROTO_UDP, int flag=NULL);
	static void ConnectTo(std::string ip);
	static void CreateSocket(IPPROTO protocol=IPPROTO_UDP);
	static bool BindSocket();

	static bool SendMsg(Convertable* message);
	static bool SendMsg(Convertable* message, sockaddr_in destinationSock);
	static bool ReceiveMsg(Convertable* message);

	static int FindClient(sockaddr_in clientAddr);
	static int AddClient(sockaddr_in clientAddr);

	static bool ShutdownSocket();
	static void CloseWinsock();

private:
	static int m_maxClients;

	//The socket here
	static SOCKET m_socket;

	//The information
	static struct addrinfo* m_ptr;
	static struct addrinfo m_hints;

	//Addresses of sockets that have sent the server messages
	static struct std::vector<sockaddr_in> m_addresses;
};


