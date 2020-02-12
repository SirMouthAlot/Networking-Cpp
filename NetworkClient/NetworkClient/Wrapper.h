#pragma once
#include "Client.h"

#ifdef __cplusplus
extern "C"
{
#endif

	PLUGIN_API void InitClient();
	PLUGIN_API void ConnectToServer(const char* ip);

	PLUGIN_API void SendFloat(float flt, MessageFlags flag);
	PLUGIN_API void SendInt(int it, MessageFlags flag);
	PLUGIN_API void SendString(const char* str, MessageFlags flag);

	PLUGIN_API float RecvFloat();
	PLUGIN_API int RecvInt();
	PLUGIN_API std::string RecvString();

#ifdef __cplusplus
}
#endif