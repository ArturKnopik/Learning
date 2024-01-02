#include "TcpServer.h"
#include "ConnectionManager.h"

TcpServer::TcpServer(boost::asio::io_context& io_context, const boost::asio::ip::tcp::endpoint& endpoint) :
    m_acceptor(io_context, endpoint), m_io_service(io_context)
{
	accept();
}

void TcpServer::broadcast(std::shared_ptr<Message> msg)
{
	if (!msg) {
		return;
	}

	for (auto connection : ConnectionManager::getInstance().getAllConnections()) {
		std::cout << "thread send msg: " << msg->getLength() << std::endl;
		connection->deliver(msg);
	}
}

void TcpServer::accept()
{
	m_acceptor.async_accept([this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket) {
		if (!ec) {
			std::shared_ptr<TcpConnection> connection =
			    std::make_shared<TcpConnection>(std::move(socket), m_io_service);
			ConnectionManager::getInstance().addConnection(connection);
			connection->start();
		}

		accept();
	});
}
