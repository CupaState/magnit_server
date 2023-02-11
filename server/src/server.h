#pragma once

#include <boost/asio.hpp>

class TcpServer
{
public:
	TcpServer(boost::asio::io_context& io_context, unsigned short port)
		: acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
	{
		start_accept();
	}

private:
	void start_accept();

	// properties
	boost::asio::ip::tcp::acceptor acceptor_;
};
