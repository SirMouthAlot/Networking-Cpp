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
	//Combine all the shit together into one message
	std::string mess;
	mess += Int((int)type).ToString();
	mess += " ";
	mess += message->ToString();
	mess += " ";
	mess += Int((int)flags).ToString();

	//Send message type
	//NetworkingWrapper::SendMsg(m_cliSock, &Int((int)type), m_ptr);
	//Send actual message
	NetworkingWrapper::SendMsg(m_cliSock, &String(mess), m_ptr);
	//Send message flags
	//NetworkingWrapper::SendMsg(m_cliSock, &Int((int)flags), m_ptr);
}

void Client::RecvMsg(MessageType& type, Convertable* message)
{
	//Gets message tyoe
	std::string mess;
	NetworkingWrapper::ReceiveMsg(m_cliSock, &mess);

	int messType;
	//Store message type
	sscanf_s(mess.c_str(), "%i", &messType);

	int messFlag;

	type = MessageType(messType);

	//Performs switch statement stuffs
	MessageTypeSwitch(mess, messType, message);
}

sockaddr_in Client::GetAddress() const
{
	return m_clientAddress;
}

void Client::ShutdownClient()
{
	NetworkingWrapper::ShutdownSocket(m_cliSock, m_ptr);
}

void Client::MessageTypeSwitch(std::string mess, int type, Convertable* message)
{
	switch ((MessageType)type)
	{
	case MessageType::MSG_INT:
	{
		int messMess;
		sscanf_s(mess.c_str(), "%i %i", &type, &messMess);

		//Share the message
		*message = Int(messMess);
		break;
	}
	case MessageType::MSG_FLOAT:
	{
		float messMess;
		sscanf_s(mess.c_str(), "%i %f", &type, &messMess);

		//Share the message
		*message = Float(messMess);
		break;
	}
	case MessageType::MSG_STRING:
	{
		std::string messMess;
		sscanf_s(mess.c_str(), "%i %s", &type, &messMess);

		//Share the message
		*message = String(messMess);
		break;
	}
	case MessageType::MSG_VECTOR3:
	{
		Vector3 messMess;
		sscanf_s(mess.c_str(), "%i %f %f %f", &type, &messMess.x, &messMess.y, &messMess.z);

		//Share the message
		*message = Vector3(messMess);
		break;
	}
	}
}
