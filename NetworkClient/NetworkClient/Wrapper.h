#pragma once
#include "NetworkingWrapper.h"

#ifdef __cplusplus
extern "C"
{
#endif

	//Put your functions here
	PLUGIN_API bool StartupWinsock();
	PLUGIN_API void SetupHints();
	PLUGIN_API void ConnectTo(const char* ip);

	PLUGIN_API void CreateSocket();

	PLUGIN_API bool SendFloat(float flt);
	PLUGIN_API bool SendInt(int it);
	PLUGIN_API bool SendString(const char* str);

	PLUGIN_API bool ShutdownWinsock();

#ifdef __cplusplus
}
#endif