#include <iostream>

#include "../Shared/Message.h"
#include "boost/asio.hpp"
#include "Client.h"
#include <thread>

int main()
{
	std::cout << "Hello World Client!\n";
	try {
		boost::asio::io_service ioService;
		Client client(ioService, "127.0.0.1", 1234);
		ioService.run();
		client.start();
		std::cout << "MSG sended" << std::endl;
		client.asyncWrite("Test-1");
		std::cout << "press eneter  to send msg" << std::endl;
		std::cin.get();
		client.asyncWrite("Test1");
		std::cin.get();
		client.asyncWrite("Trololo");
		std::cin.get();
		client.asyncWrite("XXDDD");

		std::cin.get();

		std::cin.get();
	}
	catch (const std::exception& e) {
		std::cerr << "Exception in client: " << e.what() << std::endl;
	}


	std::cin.get();
}
