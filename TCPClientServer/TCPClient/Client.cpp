#include "Client.h"
#include "boost/asio.hpp"
#include <iostream>

Client::Client(boost::asio::io_service& ioService, const std::string& serverAddress, short port)
	: m_socket(ioService)
{
	boost::asio::ip::tcp::resolver resolver(ioService);
	boost::asio::connect(m_socket, resolver.resolve({ serverAddress, std::to_string(port) }));
}

void Client::start() {
	asyncRead();
}

void Client::asyncRead() {
	boost::asio::async_read(m_socket, boost::asio::buffer(m_readMessage.getMessageInfo().m_begin, NET_MESSAGE_BUFFER_SIZE),
		[this](boost::system::error_code ec, std::size_t bytesTransferred) {
			if (!ec) {
				std::cout << "Received response: " << m_readMessage.getString();
			}
		}
	);
}

void Client::asyncWrite(const std::string& message) {
	boost::asio::async_write(m_socket, boost::asio::buffer(m_writeMessage.getMessageInfo().m_begin, m_writeMessage.getMessageInfo().m_size),
		[this](boost::system::error_code ec, std::size_t length) {
			if (!ec) {
				asyncRead();
			}
		}
	);
}