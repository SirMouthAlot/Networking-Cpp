#include "Wrapper.h"

Client myClient;

PLUGIN_API void InitClient()
{
	return myClient.InitClient();
}

PLUGIN_API void ConnectToServer(const char* ip)
{
	return myClient.ConnectToServer(ip);
}

PLUGIN_API void SendFloat(float flt, MessageFlags flag)
{
	Float temp(flt);
	return myClient.SendMsg(MessageType::MSG_FLOAT, &temp, flag);
}

PLUGIN_API void SendInt(int it, MessageFlags flag)
{
	Int temp(it);
	return myClient.SendMsg(MessageType::MSG_INT, &temp, flag);
}

PLUGIN_API void SendString(const char* str, MessageFlags flag)
{
	String temp(str);
	return myClient.SendMsg(MessageType::MSG_STRING, &temp, flag);
}

PLUGIN_API float RecvFloat()
{
	Float temp;
	MessageType type;
	myClient.RecvMsg(type, &temp);

	return temp.m_float;
}

int RecvInt()
{
	Int temp;
	MessageType type;
	myClient.RecvMsg(type, &temp);

	return temp.m_int;
}

PLUGIN_API std::string RecvString()
{
	String temp;
	MessageType type;
	myClient.RecvMsg(type, &temp);
	
	std::string test = temp.m_string;
	return test;
}
