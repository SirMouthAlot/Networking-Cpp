#include "Client.h"

Client::Client(sockaddr_in address)
{
	m_clientAddress = address;
}

void Client::InitClient()
{
	NetworkingWrapper::StartupWinsock();
	m_hints = NetworkingWrapper::SetupHints();
}

void Client::ConnectToServer(const char* ip)
{
	NetworkingWrapper::ConnectToServer(ip, m_hints, &m_ptr);
	m_cliSock = NetworkingWrapper::CreateSocket(IPPROTO_UDP);

	//Sends a connection request
	SendMsg(MessageType::MSG_CONNECT, &String("Connect"), MessageFlags::NONE);

	//Get back the client number for this client
	Int clientNum;
	MessageType type;
	RecvMsg(type, &clientNum);

	//Store it
	m_clientNum = clientNum.m_int;

	printf("You are client number %i\n", clientNum.m_int);
}

void Client::DisconnectFromServer()
{
	//Sends a disconnect request
	SendMsg(MessageType::MSG_DISCONNECT, &String("Disconnect"), MessageFlags::NONE);
}

void Client::SendMsg(MessageType type, Convertable* message, MessageFlags flags)
{
	//Send message type
	NetworkingWrapper::SendMsg(m_cliSock, &Int((int)type), m_ptr);
	//Send actual message
	NetworkingWrapper::SendMsg(m_cliSock, message, m_ptr);
	//Send message flags
	NetworkingWrapper::SendMsg(m_cliSock, &Int((int)flags), m_ptr);
}

void Client::RecvMsg(MessageType& type, Convertable* message)
{
	//Gets message
	std::string messageType;
	NetworkingWrapper::ReceiveMsg(m_cliSock, &messageType);
	Int messType;
	messType.SetValue(messageType);

	type = (MessageType)messType.m_int;

	std::string mess;
	NetworkingWrapper::ReceiveMsg(m_cliSock, &mess);

	//Converts value and stores in message
	message->SetValue(mess);
}

sockaddr_in Client::GetAddress() const
{
	return m_clientAddress;
}
