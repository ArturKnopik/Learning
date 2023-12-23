#include "Connection.h"

Connection::Connection(boost::asio::io_service& ioService)
	: m_socket(ioService)
{
}

boost::asio::ip::tcp::socket& Connection::socket()
{
	return m_socket;
}

void Connection::start() {
	asyncRead();
}

void Connection::asyncRead() {
	auto self(shared_from_this());
	boost::asio::async_read(m_socket,
		boost::asio::buffer(m_readMessage.getMessageInfo().m_begin, NET_MESSAGE_BUFFER_SIZE),
		[this, self](boost::system::error_code ec, std::size_t length) {
			if (!ec) {
				std::cout << "Received message: " << m_readMessage.getString();

				asyncWrite("Server received: " + m_readMessage.getString());
			}
		}
	);
}

void Connection::asyncWrite(const std::string& message) {
	auto self(shared_from_this());
	boost::asio::async_write(m_socket, boost::asio::buffer(m_writeMessage.getMessageInfo().m_begin, m_writeMessage.getMessageInfo().m_size),
		[this, self](boost::system::error_code ec, std::size_t /*length*/) {
			if (!ec) {
				asyncRead();
			}
		}
	);
}
