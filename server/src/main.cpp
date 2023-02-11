// boost
#include <boost/asio.hpp>

// local
#include "server.h"
#include "tcp_connection.h"

// number of port
constexpr int PORT = 12345;

int main(void)
{
	try
	{
		io_context io_context;
		TcpServer server(io_context, PORT);
		io_context.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
