// std
#include <iostream>
#include <fstream>

// boost
#include <boost/asio.hpp>

// local
#include "../../utils/file_utils.h"

// usings
using namespace boost::asio;
using namespace boost::asio::ip;

// address
constexpr const char* IP = "127.0.0.1";
// number of port
constexpr const char* PORT = "12345";
// relation path to protocol file
constexpr const char* PROTOCOL_FILE = "../protocol.txt";

int main(int argc, char *argv[])
{
  try 
  {
    if (argc != 2) 
    {
      std::cerr << "Usage: client <filename>" << std::endl;
      return 1;
    }

    boost::asio::io_context io;
    tcp::socket s(io);

    tcp::resolver resolver(io);
    boost::asio::connect(s, resolver.resolve(IP, PORT));

    std::ifstream infile(argv[1]);
    std::string line;

    // write to socket
    while (std::getline(infile, line))
      boost::asio::write(s, boost::asio::buffer(line + '\n'));
    boost::asio::write(s, boost::asio::buffer("\r\n")); // send "trigger" symbols

    int response = 0;
    s.read_some(boost::asio::buffer(&response, sizeof(response)));

    // write response to protocol
    write_protocol(response, PROTOCOL_FILE);
  } 
  catch (const std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
