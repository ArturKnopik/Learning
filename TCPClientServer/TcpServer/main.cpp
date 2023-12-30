#include "../Shared/Message.h"
#include "TcpServer.h"

int main(int argc, char* argv[])
{
	try {
		boost::asio::io_context io_context;

		boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 12345);
		TcpServer server(io_context, endpoint);
		/*
		std::thread thread([servers = &server]() {
			while (1) {
				std::string str = "Test server msg";
				std::shared_ptr<Message> msg = std::make_unique<Message>();
				msg->addString(str);
				msg->writeMessageLength();
				servers->broadcast(msg);
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			}
		});
		thread.detach();
		*/
		io_context.run();
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}