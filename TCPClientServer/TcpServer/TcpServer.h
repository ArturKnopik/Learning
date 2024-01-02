#pragma once

#include "../Shared/Message.h"
#include "TcpConnection.h"
#include "boost/asio.hpp"

#include <iostream>

class TcpServer
{
public:
	TcpServer(boost::asio::io_context& io_context, const boost::asio::ip::tcp::endpoint& endpoint);

	void broadcast(std::shared_ptr<Message> msg);

private:
	void accept();

	boost::asio::ip::tcp::acceptor m_acceptor;
	boost::asio::io_service& m_io_service;
};
