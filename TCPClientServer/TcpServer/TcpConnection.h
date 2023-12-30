#pragma once
#include "../Shared/Message.h"
#include "boost/asio.hpp"

#include <memory>
#include <queue>

constexpr size_t CONNECTION_TIMEOUT = 30;

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
public:
	TcpConnection(boost::asio::ip::tcp::socket socket, boost::asio::io_service& io_service);

	~TcpConnection();

	void start();

	void deliver(std::shared_ptr<Message> msg);

	void closeSocket();

	static void handleTimeout(std::weak_ptr<TcpConnection> connectionWeak, const boost::system::error_code& error);

private:
	void readHeader();

	void readBody();

	void internalWrite();

	boost::asio::steady_timer m_readTimer;
	boost::asio::steady_timer m_writeTimer;
	boost::asio::ip::tcp::socket m_socket;
	Message m_read_msg;
	std::deque<std::shared_ptr<Message>> m_writeMessages;
	boost::asio::io_service& m_io_service;
	std::recursive_mutex m_mutex;
};