#include "NetworkingWrapper.h"
#include "Wrapper.h"

int main()
{	
	StartupWinsock();
	SetupHints();
	ConnectTo("192.168.137.184");
	CreateSocket();
	SendString("Love you<3");
	SendFloat(12.5f);
	SendInt(3);
	system("pause");
	ShutdownWinsock();

	return 0;
}