#include "Server.h"
#include <thread>

bool ExitProgram(Server server)
{
	while (true)
	{
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			server.CloseServer();

			exit(0);
		}
	}
}


int main()
{
	Server myServer;

	//Start a separate thread for exiting program
	std::thread t1;
	t1 = std::thread(ExitProgram, myServer);
	t1.detach();

	//Server stuffs
	myServer.InitServer();

	while (true)
	{
		myServer.RecvMsg();
	}


	return 0;
}