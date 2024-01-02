//
// chat_client.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2023 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "../Shared/Message.h"

#include <boost/asio.hpp>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>

class TcpClient
{
public:
	TcpClient(boost::asio::io_context& io_context, const boost::asio::ip::tcp::resolver::results_type& endpoints) :
	    m_ioContext(io_context), m_socket(io_context)
	{
		connect(endpoints);
	}

	void send(std::shared_ptr<Message> msg)
	{
		boost::asio::post(m_ioContext, [this, msg]() {
			bool write_in_progress = !m_writeMessages.empty();
			m_writeMessages.push_back(msg);
			if (!write_in_progress) {
				internalWrite();
			}
		});
	}

	void close()
	{
		boost::asio::post(m_ioContext, [this]() { m_socket.close(); });
	}

private:
	void connect(const boost::asio::ip::tcp::resolver::results_type& endpoints)
	{
		boost::asio::async_connect(m_socket, endpoints,
		                           [this](boost::system::error_code ec, boost::asio::ip::tcp::endpoint) {
			                           if (!ec) {
				                           readHeader();
			                           }
		                           });
	}

	void readHeader()
	{
		boost::asio::async_read(
		    m_socket, boost::asio::buffer(m_readMessage.getBuffer(), HEADER_LENGTH),
		    [this](boost::system::error_code ec, std::size_t length) {
			    m_readMessage.setLength(m_readMessage.getLengthFromHeader());
			    std::cout << "HEAD msg size  : " << m_readMessage.getLength() << std::endl;
			    std::cout<< " m_readMessage.getLengthFromHeader():   " << m_readMessage.getLengthFromHeader() << std::endl;
			    if ((!ec) && m_readMessage.getLengthFromHeader()) {
				    readBody();
			    } else {
				    std::cerr << "Exception: " << ec.what() << "\n";
				    m_socket.close();
			    }
		    });
	}

	void readBody()
	{
		auto ln = m_readMessage.getLength();
		auto charS = m_readMessage.getBodyBuffer();

		auto size = m_readMessage.getLengthFromHeader();
		m_readMessage.setLength(size + HEADER_LENGTH);
		boost::asio::async_read(
		    m_socket, boost::asio::buffer(m_readMessage.getBodyBuffer(), m_readMessage.getLength() - HEADER_LENGTH),
		    [this](boost::system::error_code ec, std::size_t length) {
			    auto ln = m_readMessage.getLength();
			    auto charS = m_readMessage.getBodyBuffer();
			    std::cout << "BODY msg size  : " << m_readMessage.getLength() << std::endl;
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

private:
	void internalWrite()
	{
		boost::asio::async_write(m_socket,
		                         boost::asio::buffer(m_writeMessages.front()->getBuffer(),
		                                             m_writeMessages.front()->getLength() + HEADER_LENGTH),
		                         [this](boost::system::error_code ec, std::size_t /*length*/) {
			                         if (!ec) {
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

	void writeHandler(const boost::system::error_code& ec, std::size_t length)
	{
		std::cout << ec << std::endl;
		if (!ec && m_writeMessages.size() > 0) {
			m_writeMessages.pop_front();
			if (!m_writeMessages.empty()) {
				internalWrite();
			}
		} else {
			m_socket.close();
		}
	}

	boost::asio::io_context& m_ioContext;
	boost::asio::ip::tcp::socket m_socket;
	Message m_readMessage;
	std::deque<std::shared_ptr<Message>> m_writeMessages;
	std::recursive_mutex m_mutex;
};

int main(int argc, char* argv[])
{
	try {
		boost::asio::io_context io_context;

		boost::asio::ip::tcp::resolver resolver(io_context);
		auto endpoints = resolver.resolve(boost::asio::ip::tcp::v4(), "localhost", "12345");
		TcpClient client(io_context, endpoints);

		std::thread t([&io_context]() {
			std::cout << "[I] io_context:run: " << std::endl;
			io_context.run();
			std::cout << "[I] io_context:stop: " << std::endl;
		});

		char line[MAX_BODY_LENGTH + 1];
		// while (1 == 1) {
		std::shared_ptr<Message> msg = std::make_unique<Message>();
		msg->addByte('a');
		msg->writeMessageLength();
		client.send(msg);
		std::cout << "send" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
		//}

		// client.close();
		std::this_thread::sleep_for(std::chrono::milliseconds(300000));
		t.join();
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}