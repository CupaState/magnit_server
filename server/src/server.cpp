// local
#include "server.h"
#include "tcp_connection.h"
#include "../../utils/file_utils.h"

// relation path to protocol file
constexpr const char* PROTOCOL_FILE = "../protocol.txt";

// to specify in which side error occured
constexpr const char* SERVER = "Server: "; 

void TcpServer::start_accept()
{   
  auto new_connection = std::make_shared<TcpConnection>(static_cast<boost::asio::io_context&>(acceptor_.get_executor().context()));
  acceptor_.async_accept(new_connection->socket(),
    [this, new_connection](const boost::system::error_code& error)
    {
      if (!error)
        new_connection->start();
      else
        write_protocol(SERVER + error.message(), PROTOCOL_FILE);
      start_accept();
    });
}
