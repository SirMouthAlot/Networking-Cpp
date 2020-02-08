#include "NetworkingWrapper.h"

int main()
{
	NetworkingWrapper::StartupWinsock();
	NetworkingWrapper::SetupHints(AF_INET, SOCK_DGRAM, IPPROTO_UDP, AI_PASSIVE);
	NetworkingWrapper::ConnectTo("");

	NetworkingWrapper::CreateSocket(IPPROTO_UDP);
	NetworkingWrapper::BindSocket();

	while (true)
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

	system("pause");

	NetworkingWrapper::CloseWinsock();

	return 0;
}