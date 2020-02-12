#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "NetworkingWrapper.h"

enum class MessageType
{
	MSG_INT,				//Message type Int
	MSG_FLOAT,				//Message type Float
	MSG_DOUBLE,				//Message type Double
	MSG_VECTOR3,			//Message type Vector3 (unimplemented)
	MSG_STRING,				//Message type String
	MSG_CONNECT,			//Message type Connect Request
	MSG_DISCONNECT,			//Message type Disconnect Request
};

enum class MessageFlags
{

	BROADCAST_ALL,			//Broadcast to all clients connected to the server
	BROADCAST_RELATED,		//Broadcast to only clients grouped with this client
	NONE					//Do nothing
};

class Client
{
public:
	Client() { }
	Client(sockaddr_in address);
	~Client() { };

	void InitClient();

	void ConnectToServer(const char* ip);
	void DisconnectFromServer();

	void SendMsg(MessageType type, Convertable* message, MessageFlags flags);
	void RecvMsg(MessageType& type, Convertable* message);

	sockaddr_in GetAddress() const;

	void ShutdownClient();

	int m_clientNum;
private:

	void MessageTypeSwitch(std::string mess, int type, Convertable* message);

	SOCKET m_cliSock;
	struct addrinfo* m_ptr = NULL, m_hints;

	sockaddr_in m_clientAddress;
};

struct ClientCompare
{
public:
	ClientCompare(Client* client) : m_client(client) { }

	bool operator()(Client* compare) const
	{
		bool addressSame = (m_client->GetAddress().sin_addr.S_un.S_addr == compare->GetAddress().sin_addr.S_un.S_addr);
		bool familySame = m_client->GetAddress().sin_family == compare->GetAddress().sin_family;
		bool portSame = m_client->GetAddress().sin_port == compare->GetAddress().sin_port;

		return (addressSame && familySame && portSame);
	}

	Client* m_client;
};


#endif // !__CLIENT_H__
