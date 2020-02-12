#include "NetworkingWrapper.h"
#include "Wrapper.h"
#include <thread>

void ReceiveStrings()
{
	while (true)
	{
		//printf("ID number: %i \n", RecvInt());
		std::cout << RecvVector() << std::endl;
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

	float i = 0.0001f;	
	while (true)
	{
		SendInt(201, MessageFlags::BROADCAST_ALL);
		SendVector(Vector3CS(0.f, -9.f, i), MessageFlags::BROADCAST_ALL);
		i += 0.0001f;
	}

	return 0;
}