#pragma once

#include "../Shared/Message.h"
#include "boost/asio.hpp"

class Client {
public:
	Client(boost::asio::io_service& ioService, const std::string& serverAddress, short port);

	void start();
	void asyncRead();
	void asyncWrite(const std::string& message);
private:

	boost::asio::ip::tcp::socket m_socket;
	Message m_readMessage;
	Message m_writeMessage;
};

