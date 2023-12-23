#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include "../Shared/Message.h"

class Connection : public std::enable_shared_from_this<Connection> {
public:
    Connection(boost::asio::io_service& ioService);

    boost::asio::ip::tcp::socket& socket();
    void start();
    void asyncWrite(const std::string& message);

private:
    void asyncRead();


    boost::asio::ip::tcp::socket m_socket;
    Message m_readMessage;
    Message m_writeMessage;
};