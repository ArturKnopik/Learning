#include "../Shared/Message.h"
#include "TcpServer.h"

int main(int argc, char* argv[])
{
	try {
		boost::asio::io_context io_context;

		boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 12345);
		TcpServer server(io_context, endpoint);

		std::thread thread([&io_context]() { io_context.run(); });
		std::this_thread::sleep_for(std::chrono::milliseconds(10000));
		std::thread sendertHREAD([servers = &server]() {
			while (1 == 2) {
				std::string str = "1234";
				std::shared_ptr<Message> msg = std::make_unique<Message>();
				msg->addByte('a');
				msg->addByte('b');
				msg->addByte('c');
				msg->addString(str);
				msg->writeMessageLength();
				servers->broadcast(msg);
				std::this_thread::sleep_for(std::chrono::milliseconds(30));
			}
		});
		sendertHREAD.detach();
		thread.join();
		std::this_thread::sleep_for(std::chrono::milliseconds(60000));
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}