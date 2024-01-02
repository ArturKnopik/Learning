#include "TcpConnection.h"

#include "ConnectionManager.h"

#include <iostream>

TcpConnection::TcpConnection(boost::asio::ip::tcp::socket socket, boost::asio::io_service& io_service) :
    m_socket(std::move(socket)), m_readTimer(io_service), m_writeTimer(io_service), m_io_service(io_service)
{}

TcpConnection::~TcpConnection() { closeSocket(); }

void TcpConnection::start() { readHeader(); }

void TcpConnection::deliver(std::shared_ptr<Message> msg)
{
	if (!msg) {
		return;
	}

	bool write_in_progress = !m_writeMessages.empty();
	{
		std::lock_guard lock(m_mutex);
		m_writeMessages.push_back(msg);
	}

	if (!write_in_progress) {
		internalWrite();
	}
}

void TcpConnection::readHeader()
{
	std::lock_guard lock(m_mutex);
	m_readMessage.reset();
	m_readTimer.cancel();
	try {
		m_readTimer.expires_from_now(std::chrono::seconds(CONNECTION_TIMEOUT));
		m_readMessage = {};
		m_readTimer.async_wait(
		    [thisPtr = std::weak_ptr<TcpConnection>(shared_from_this())](const boost::system::error_code& error) {
			    TcpConnection::handleTimeout(thisPtr, error);
		    });

		auto self(shared_from_this());
		boost::asio::async_read(m_socket, boost::asio::buffer(m_readMessage.getBuffer(), HEADER_LENGTH),
		                        [this, self](boost::system::error_code ec, std::size_t length) {
			                        m_readTimer.cancel();
			                        if (!ec && m_readMessage.getLengthFromHeader()) {
				                        readBody();
			                        } else {
				                        std::cout << "[Network error - Connection::internalSend] " << ec.what()
				                                  << std::endl;
				                        closeSocket();
			                        }
		                        });
	} catch (boost::system::system_error& e) {
		std::cout << "[Network error - Connection::internalSend] " << e.what() << std::endl;
		closeSocket();
	}
}

void TcpConnection::readBody()
{
	std::lock_guard lock(m_mutex);

	m_readTimer.expires_from_now(std::chrono::seconds(CONNECTION_TIMEOUT));
	m_readTimer.async_wait(
	    [thisPtr = std::weak_ptr<TcpConnection>(shared_from_this())](const boost::system::error_code& error) {
		    TcpConnection::handleTimeout(thisPtr, error);
	    });

	auto self(shared_from_this());
	boost::asio::async_read(
	    m_socket, boost::asio::buffer(m_readMessage.getBodyBuffer(), m_readMessage.getLength() - HEADER_LENGTH),
	                        [this, self](boost::system::error_code ec, std::size_t length) {
		                        m_readTimer.cancel();
		                        if (!ec) {
			                        std::cout.write(reinterpret_cast<char*>(m_readMessage.getBodyBuffer()),
			                                        m_readMessage.getLength()); //  \0 not stop string writing
			                        std::cout << "\n";
			                        readHeader();
		                        } else {
			                        closeSocket();
		                        }
	                        });
}

void TcpConnection::internalWrite()
{
	try {
		m_writeTimer.expires_from_now(std::chrono::seconds(CONNECTION_TIMEOUT));
		m_writeTimer.async_wait(
		    [thisPtr = std::weak_ptr<TcpConnection>(shared_from_this())](const boost::system::error_code& error) {
			    TcpConnection::handleTimeout(thisPtr, error);
		    });

		auto self = shared_from_this();
		auto sz = m_writeMessages.front()->getLength() + HEADER_LENGTH;
		boost::asio::async_write(m_socket,
		                         boost::asio::buffer(m_writeMessages.front()->getBuffer(),
		                                             m_writeMessages.front()->getLength() + HEADER_LENGTH),
		                         [this, self](boost::system::error_code ec, std::size_t length) {
			                         auto sz = m_writeMessages.front()->getLength() + HEADER_LENGTH;
			                         auto bf = m_writeMessages.front()->getBuffer();
			                         auto ln = m_writeMessages.front()->getLength();
			                         std::lock_guard lock(m_mutex);
			                         m_writeTimer.cancel();
			                         if (!ec) {
				                         m_writeMessages.pop_front();
				                         if (!m_writeMessages.empty()) {
					                         internalWrite();
				                         }
			                         } else {
				                         m_writeMessages.clear();
				                         std::cout << "[E] TcpConnection::internalWrite: " << ec.what() << std::endl;

				                         closeSocket();
			                         }
		                         });
	} catch (boost::system::system_error& e) {
		std::cout << "[E] Network error - Connection::internalSend: " << e.what() << std::endl;
		closeSocket();
	}
}

void TcpConnection::closeSocket()
{
	if (m_socket.is_open()) {
		try {
			m_readTimer.cancel();
			m_writeTimer.cancel();
			boost::system::error_code error;
			m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, error);
			m_socket.close(error);
			ConnectionManager::getInstance().removeConnection(shared_from_this());
		} catch (boost::system::system_error& e) {
			std::cout << "TcpConnection::closeSocket - fail to close connection " << e.what() << std::endl;
		}
	}
}

void TcpConnection::handleTimeout(std::weak_ptr<TcpConnection> connectionWeak, const boost::system::error_code& error)
{
	if (error == boost::asio::error::operation_aborted) {
		// The timer has been cancelled manually
		return;
	}

	if (auto connection = connectionWeak.lock()) {
		connection->closeSocket();
	}
}