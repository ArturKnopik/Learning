#include "boost/asio.hpp"
#include "TcpClient.h"
#include <iostream>

int main(int argc, char* argv[])
{
	try {
		boost::asio::io_context io_context;

		boost::asio::ip::tcp::resolver resolver(io_context);
		auto endpoints = resolver.resolve(boost::asio::ip::tcp::v4(), "localhost", "12345");
		TcpClient client(io_context, endpoints);

		std::thread thread([&io_context]() {
			std::cout << "[I] io_context:run" << std::endl;
			io_context.run();
			std::cout << "[I] io_context:stop" << std::endl;
		});

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		for (size_t i = 0; i < 10; i++) {
			std::shared_ptr<Message> msg = std::make_unique<Message>();
			msg->addByte('a');
			msg->addString("TEST_STR!!!!");
			msg->writeMessageLength();
			client.send(msg);
			std::cout << "[I] main - msg sended" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cout << "[I] main - close client" << std::endl;
		client.close();
		thread.join();
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}