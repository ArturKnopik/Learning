#include "Server.h"

#include <memory>

Server::Server(boost::asio::io_service& ioService, short port)
    : m_acceptor(ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
    m_socket(ioService), m_ioService(ioService)
{
    startAccept();
}

void Server::startAccept()
{
    m_connection = std::make_shared<Connection>(m_ioService);
    m_acceptor.async_accept(m_connection->socket(),
        [this, connection = m_connection](const boost::system::error_code& error) {
            std::cout << "Connection" << std::endl;

            if (!error) {
                connection->start();
            }
            else
            {
                std::cout << "Connection status" << error << std::endl;
            }
            connection->asyncWrite("Welcome to the server!");
            startAccept();
        });
}