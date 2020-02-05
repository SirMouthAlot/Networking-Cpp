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
		Float x, y, z;
		NetworkingWrapper::ReceiveMsg(&x);
		NetworkingWrapper::ReceiveMsg(&y);
		NetworkingWrapper::ReceiveMsg(&z);

		printf("Ship position: (%f, %f, %f)\n", x.m_float, y.m_float, z.m_float);
	}

	system("pause");

	NetworkingWrapper::CloseWinsock();

	return 0;
}