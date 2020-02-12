#include "Server.h"
#include <thread>

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

void ReceiveMessages(Server server)
{
	while (true)
	{
		server.RecvMsg();
	}
}


int main()
{
	//Start a separate thread for exiting program
	std::thread t1;
	t1 = std::thread(ExitProgram);
	t1.detach();

	//Server stuffs
	Server myServer;
	myServer.InitServer();

	while (true)
	{
		myServer.RecvMsg();
	}

	return 0;
}