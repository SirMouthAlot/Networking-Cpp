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
	NetworkingWrapper::ConnectTo(ip, m_hints, &m_ptr);
	m_cliSock = NetworkingWrapper::CreateSocket(IPPROTO_UDP);

	//Sends a connection request
	SendMsg(MessageType::MSG_CONNECT, &String("Connect"), MessageFlags::NONE);

	Int clientNum;
	MessageType type;
	RecvMsg(type, &clientNum);

	printf("You are client %i\n", clientNum.m_int);

	//Store it
	m_clientNum = clientNum.m_int;
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
	//Gets message tyoe
	std::string messageType;
	NetworkingWrapper::ReceiveMsg(m_cliSock, &messageType);
	Int messType;
	messType.SetValue(messageType);
	//Stores type
	type = (MessageType)messType.m_int;

	//Gets message
	std::string mess;
	NetworkingWrapper::ReceiveMsg(m_cliSock, &mess);

	//Converts value and stores in message
	message->SetValue(mess);
}

sockaddr_in Client::GetAddress() const
{
	return m_clientAddress;
}

void Client::ShutdownClient()
{
	NetworkingWrapper::ShutdownSocket(m_cliSock, m_ptr);
}
