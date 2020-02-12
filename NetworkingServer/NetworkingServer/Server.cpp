#include "Server.h"

Server::Server()
{
}

Server::~Server()
{
	for (int i = 0; i < m_clients.size(); i++)
	{
		if (m_clients[i] != nullptr)
		{
			delete m_clients[i];
			m_clients[i] = nullptr;
		}
	}
}

void Server::InitServer()
{
	if (!NetworkingWrapper::StartupWinsock())
	{
		printf("Winsock failed to start up!");
	}

	m_hints = NetworkingWrapper::SetupHints(AF_INET, SOCK_DGRAM, IPPROTO_UDP, AI_PASSIVE);

	NetworkingWrapper::ConnectTo("", m_hints, &m_ptr);

	m_serverSock = NetworkingWrapper::CreateSocket(IPPROTO_UDP);
	NetworkingWrapper::BindSocket(m_serverSock, m_ptr);

}

void Server::SendMsg(MessageType type, Convertable* message, Client client)
{
	//Casts message type to int
	Int messageType((int)type);

	//Send message type first
	NetworkingWrapper::SendMsg(m_serverSock, &messageType, client.GetAddress());

	//Send actual message
	NetworkingWrapper::SendMsg(m_serverSock, message, client.GetAddress());
}

void Server::RecvMsg()
{
	Int tempType;
	std::string typeMessage;

	sockaddr_in clientAddr;
	clientAddr = NetworkingWrapper::ReceiveMsg(m_serverSock, &typeMessage);

	//Converts to int
	tempType.SetValue(typeMessage);

	Convertable* tempMessage = nullptr;;

	//if client was on list
	bool onList = false;
	Client* client;
	int clientNum = -1;

	switch ((MessageType)tempType.m_int)
	{
		
	case MessageType::MSG_CONNECT:
		//Check if this client is on the list, if not add it
		client = new Client(clientAddr);

		//If client is in the list already
		FindClient(client, onList);
		if (onList)
		{
			delete client;
			client = nullptr;
		}

		break;
	case MessageType::MSG_DISCONNECT:
		client = new Client(clientAddr);

		//Find client on list
		clientNum = FindClient(client, onList);
		if (onList)
		{
			if (m_clients[clientNum] != nullptr)
			{
				//Cleans up data
				delete m_clients[clientNum];
				m_clients[clientNum] = nullptr;
			}

			//Removes client from list
			m_clients.erase(m_clients.begin() + clientNum);
		}
		delete client;
		client = nullptr;
		break;
	case MessageType::MSG_INT:
		tempMessage = new Int();
		break;
	case MessageType::MSG_FLOAT:
		tempMessage = new Float();
		break;
	case MessageType::MSG_DOUBLE:
		tempMessage = new Double();
		break;
	case MessageType::MSG_STRING:
		tempMessage = new String();
		break;
	case MessageType::MSG_VECTOR3:
		//TODO: Implement Vector3 messages
		break;
	default:
		//Do nothing
		break;
	}

	std::string messageMessage;
	NetworkingWrapper::ReceiveMsg(m_serverSock, &messageMessage);
	if (tempMessage != nullptr)
	{
		//Converts message to correct type
		tempMessage->SetValue(messageMessage);
	}

	std::string messageFlag;
	NetworkingWrapper::ReceiveMsg(m_serverSock, &messageFlag);
	Int messFlag;
	messFlag.SetValue(messageFlag);

	switch ((MessageFlags)messFlag.m_int)
	{
	case MessageFlags::BROADCAST_ALL:
		//If it's not a connect or disconnect request
		client = new Client(clientAddr);
		clientNum = FindClient(client, onList);

		for (int i = 0; i < m_clients.size(); i++)
		{
			//Broadcast the message to all clients
			if (i != clientNum)
			{
				SendMsg((MessageType)tempType.m_int, tempMessage, *m_clients[i]);
			}
		}

		break;
	case MessageFlags::BROADCAST_RELATED:
		//TODO: Implement this
		break;
	case MessageFlags::NONE:
		//Do nothing
		break;
	}

	//Cleanup message data
	if (tempMessage != nullptr)
	{
		delete tempMessage;
		tempMessage = nullptr;
	}

	if ((MessageType)tempType.m_int == MessageType::MSG_CONNECT && !onList)
	{
		Client clientN = Client(clientAddr);
		int clientNumN = FindClient(&clientN, onList);

		m_clients[clientNumN]->m_clientNum = clientNumN;

		//Tells client what number his client is stored at
		SendMsg(MessageType::MSG_INT, &Int(clientNumN), *m_clients[clientNumN]);
	}
}

int Server::FindClient(Client* client, bool& onList)
{
	auto it = std::find_if(m_clients.begin(), m_clients.end(), ClientCompare(client));

	if (it == m_clients.end())
	{
		onList = false;
		return AddClient(client);
	}

	//Returns the position in index
	onList = true;
	return (it - m_clients.begin());
}

int Server::AddClient(Client* client)
{
	m_clients.push_back(client);
	return m_clients.size() - 1;
}

int Server::GetNumConnected()
{
	return m_clients.size();
}
