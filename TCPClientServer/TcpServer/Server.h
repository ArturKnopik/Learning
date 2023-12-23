#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include "Connection.h"

class Server {
public:
    Server(boost::asio::io_service& ioService, short port);

private:
    void startAccept();

    boost::asio::ip::tcp::acceptor m_acceptor;
    boost::asio::ip::tcp::socket m_socket;
    boost::asio::io_service& m_ioService;
    std::shared_ptr<Connection> m_connection;
};