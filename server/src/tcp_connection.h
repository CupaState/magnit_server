#pragma once

// std
#include <iostream>

// boost
#include <boost/asio.hpp>

// local
#include "../../model/data.h"

// usings
using namespace boost::asio;
using namespace boost::asio::ip;

// size of boost::asio::streambuf
constexpr size_t BUF_SIZE = 1048576; // 2^20
// read untill this symbols
constexpr const char* UNTIL_SYM = "\r\n";
// size of UNTIL_SYM
constexpr size_t UNTIL_SYM_SIZE = sizeof(UNTIL_SYM);

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
public:
  TcpConnection(boost::asio::io_context& io_context) : m_socket(io_context) {}

  tcp::socket& socket();

  void start();

private:
/// ==================================================================================
  void do_read();
	void do_write(const int& message);

	// parses string to vector of Data structures
	std::vector<Data> parse_data(const std::string& data);

	// returns the max date and result of division corresponding numbers
	std::pair<std::string, double> calc_data(std::vector<Data>& data_vec);
/// ==================================================================================
	// properties
	tcp::socket m_socket;
	boost::asio::streambuf m_buf;
	bool is_protocol_writed = false; // to avoid multiple write protocol file in asyncronous function
};

