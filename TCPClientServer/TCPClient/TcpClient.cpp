#include "TcpClient.h"

TcpClient::TcpClient(boost::asio::io_context& io_context,
                     const boost::asio::ip::tcp::resolver::results_type& endpoints) :
    m_ioContext(io_context), m_socket(io_context)
{
	connect(endpoints);
}

void TcpClient::send(std::shared_ptr<Message> msg)
{
	boost::asio::post(m_ioContext, [this, msg]() {
		std::lock_guard lock(m_mutex);
		bool write_in_progress = !m_writeMessages.empty();
		m_writeMessages.push_back(msg);
		if (!write_in_progress) {
			internalWrite();
		}
	});
}

void TcpClient::close()
{
	boost::asio::post(m_ioContext, [this]() { m_socket.close(); });
}

void TcpClient::connect(const boost::asio::ip::tcp::resolver::results_type& endpoints)
{
	boost::asio::async_connect(m_socket, endpoints,
	                           [this](boost::system::error_code ec, boost::asio::ip::tcp::endpoint) {
		                           if (!ec) {
			                           readHeader();
		                           }
	                           });
}

void TcpClient::readHeader()
{
	boost::asio::async_read(m_socket, boost::asio::buffer(m_readMessage.getBuffer(), HEADER_LENGTH),
	                        [this](boost::system::error_code ec, std::size_t length) {
		                        std::lock_guard lock(m_mutex);
		                        m_readMessage.setLength(m_readMessage.getLengthFromHeader());
		                        if ((!ec) && m_readMessage.getLengthFromHeader()) {
			                        readBody();
		                        } else {
			                        std::cerr << "Exception: " << ec.what() << "\n";
			                        m_socket.close();
		                        }
	                        });
}

void TcpClient::readBody()
{
	auto size = m_readMessage.getLengthFromHeader();
	m_readMessage.setLength(size + HEADER_LENGTH);
	boost::asio::async_read(
	    m_socket, boost::asio::buffer(m_readMessage.getBodyBuffer(), m_readMessage.getLength() - HEADER_LENGTH),
	    [this](boost::system::error_code ec, std::size_t length) {
		    std::lock_guard lock(m_mutex);

		    if (!ec) {
			    std::cout.write(reinterpret_cast<char*>(m_readMessage.getBodyBuffer()),
			                    m_readMessage.getLength()); //  \0 not stop string writing
			    std::cout << "\n";
			    readHeader();
		    } else {
			    m_socket.close();
		    }
		    m_readMessage.reset();
	    });
}

void TcpClient::internalWrite()
{
	boost::asio::async_write(
	    m_socket,
	    boost::asio::buffer(m_writeMessages.front()->getBuffer(), m_writeMessages.front()->getLength() + HEADER_LENGTH),
	    [this](boost::system::error_code ec, std::size_t /*length*/) {
		    if (!ec) {
			    std::lock_guard lock(m_mutex);
			    if (m_writeMessages.size() > 0) {
				    m_writeMessages.pop_front();
				    if (!m_writeMessages.empty()) {
					    internalWrite();
				    }
			    }
		    } else {
			    m_socket.close();
		    }
	    });
}

void TcpClient::writeHandler(const boost::system::error_code& ec, std::size_t length)
{
	std::cout << ec << std::endl;
	std::lock_guard lock(m_mutex);
	if (!ec && m_writeMessages.size() > 0) {
		m_writeMessages.pop_front();
		if (!m_writeMessages.empty()) {
			internalWrite();
		}
	} else {
		m_socket.close();
	}
}