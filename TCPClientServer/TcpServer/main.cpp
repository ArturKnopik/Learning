#include <iostream>
#include <string>

#include "../Shared/Message.h"
#include "Server.h"
#include <boost/asio.hpp>

int main()
{
    std::cout << "Hello World Server!\n";
    try {
        boost::asio::io_service ioService;
        Server server(ioService, 1234);
        ioService.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Exception in server: " << e.what() << std::endl;
    }
	std::cin.get();
}

