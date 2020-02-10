#include "NetworkingWrapper.h"
#include <thread>

bool keepOpen = true;

void GetPositionInfo()
{
	printf("Current ship position\n");
	Float x, y, z;
	NetworkingWrapper::ReceiveMsg(&x);
	printf("%f\n", x.m_float);
	NetworkingWrapper::ReceiveMsg(&y);
	printf("%f\n", y.m_float);
	NetworkingWrapper::ReceiveMsg(&z);
	printf("%f\n", z.m_float);
	printf("\n");
}

bool ExitProgram()
{
	while (true)
	{
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			exit(0);
		}
	}
}


int main()
{
	NetworkingWrapper::StartupWinsock();
	NetworkingWrapper::SetupHints(AF_INET, SOCK_DGRAM, IPPROTO_UDP, AI_PASSIVE);
	NetworkingWrapper::ConnectTo("");

	NetworkingWrapper::CreateSocket(IPPROTO_UDP);
	NetworkingWrapper::BindSocket();

	//Start a separate thread for receiving data
	std::thread t1;

	//Keeps the exit program loop running at all times
	t1 = std::thread(ExitProgram);
	t1.detach();

	while (keepOpen)
	{
		GetPositionInfo();
	}

	system("pause");

	NetworkingWrapper::CloseWinsock();

	return 0;
}