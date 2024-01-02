#pragma once

#include "../Shared/Message.h"

#include <boost/asio.hpp>
#include <deque>
#include <iostream>
#include <memory>
#include <mutex>

class TcpClient
{
public:
	TcpClient(boost::asio::io_context& io_context, const boost::asio::ip::tcp::resolver::results_type& endpoints);

	void send(std::shared_ptr<Message> msg);
	void close();

private:
	void connect(const boost::asio::ip::tcp::resolver::results_type& endpoints);
	void readHeader();
	void readBody();
	void internalWrite();
	void writeHandler(const boost::system::error_code& ec, std::size_t length);

private:
	boost::asio::io_context& m_ioContext;
	boost::asio::ip::tcp::socket m_socket;
	Message m_readMessage;
	std::deque<std::shared_ptr<Message>> m_writeMessages;
	std::recursive_mutex m_mutex;
};