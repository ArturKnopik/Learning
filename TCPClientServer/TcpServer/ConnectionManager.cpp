#include "ConnectionManager.h"

#include <iostream>

void ConnectionManager::addConnection(std::shared_ptr<TcpConnection> connection)
{
	if (connection) {
		std::cout << "Connection added" << std::endl;
		m_connections.insert(connection);
	}
}

void ConnectionManager::removeConnection(std::shared_ptr<TcpConnection> connection)
{
	if (connection) {
		std::cout << "Connection removed" << std::endl;
		m_connections.erase(connection);
	}
}

std::set<std::shared_ptr<TcpConnection>>& ConnectionManager::getAllConnections() { return m_connections; }
