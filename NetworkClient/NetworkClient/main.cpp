#include "NetworkingWrapper.h"
#include "Wrapper.h"
#include <thread>

void ReceiveStrings()
{
	while (true)
	{
		printf("%s\n", RecvString().c_str());

		printf("%i\n", RecvInt());

		printf("%f\n", RecvFloat());
	}
}

int main()
{	
	InitClient();
	std::string ip;
	printf("Please write the server IP you wish to connect to: ");
	std::getline(std::cin, ip);
	ConnectToServer(ip.c_str());

	//Receive strings now runs independantly
	std::thread t = std::thread(ReceiveStrings);
	t.detach();

	printf("You have connected!\n");
	SendString("New Client has just connected", MessageFlags::BROADCAST_ALL);
	SendInt(69, MessageFlags::BROADCAST_ALL);
	SendFloat(69.69f, MessageFlags::BROADCAST_ALL);

	while (true)
	{

	}

	return 0;
}