#pragma once
#include "TcpConnection.h"

#include <memory>
#include <set>

class ConnectionManager
{
public:
	static ConnectionManager& getInstance()
	{
		static ConnectionManager instance;
		return instance;
	}

	void addConnection(std::shared_ptr<TcpConnection> connection);

	void removeConnection(std::shared_ptr<TcpConnection> connection);

	std::set<std::shared_ptr<TcpConnection>>& getAllConnections();

private:
	ConnectionManager() {}

	~ConnectionManager() {}

	std::set<std::shared_ptr<TcpConnection>> m_connections;
};