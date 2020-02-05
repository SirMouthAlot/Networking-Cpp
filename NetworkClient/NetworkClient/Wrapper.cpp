#include "Wrapper.h"

PLUGIN_API bool StartupWinsock()
{
	return NetworkingWrapper::StartupWinsock();
}

PLUGIN_API void SetupHints()
{
	return NetworkingWrapper::SetupHints();
}

PLUGIN_API void ConnectTo(const char* ip)
{
	return NetworkingWrapper::ConnectTo(ip);
}

PLUGIN_API void CreateSocket()
{
	return NetworkingWrapper::CreateSocket();
}

PLUGIN_API bool SendFloat(float flt)
{
	Float temp(flt);
	return NetworkingWrapper::SendMsg(&temp);
}

PLUGIN_API bool SendInt(int it)
{
	Int temp(it);
	return NetworkingWrapper::SendMsg(&temp);
}

PLUGIN_API bool SendString(const char* str)
{
	String temp(str);
	return NetworkingWrapper::SendMsg(&temp);
}

PLUGIN_API bool ShutdownWinsock()
{
	return NetworkingWrapper::ShutdownSocket();
}
