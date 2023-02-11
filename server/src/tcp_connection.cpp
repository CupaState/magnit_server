// local
#include "tcp_connection.h"
#include "../../utils/file_utils.h"
#include "../../utils/string_utils.h"

// relation path to protocol file
constexpr const char* PROTOCOL_FILE = "../protocol.txt";
// to specify in which side error occured
constexpr const char* SERVER = "TcpConnection: "; 

void TcpConnection::start()
{
  do_read();
}

tcp::socket& TcpConnection::socket()
{
  return m_socket;
}

/// ==================================================================================
void TcpConnection::do_read()
{
  auto self(shared_from_this());

  m_buf.prepare(BUF_SIZE);
  boost::asio::async_read_until(m_socket, m_buf, UNTIL_SYM,
    [this, self](const boost::system::error_code& error, size_t bytes_transferred)
    {
      if (!error)
      {
        if (!bytes_transferred)
        {
          std::string err_msg = "0 bytes transferred\n";

          std::cout << err_msg << std::endl;
          write_protocol(SERVER + err_msg, PROTOCOL_FILE);
          return;
        }

        std::string data = boost::asio::buffer_cast<const char*>(m_buf.data());
        // remove symbols from \r to end
        erase_from_symbol(data, '\r');

        // parse received data to vector of struct for further processing
        std::vector<Data> recv_data = parse_data(data);

        // calculate to write protocol
        std::pair<std::string, double> p = calc_data(recv_data);

        // write protocol file
        if (!is_protocol_writed)
        {
          write_protocol(p, PROTOCOL_FILE);
          is_protocol_writed = true;
        }

        // return number of lines to client
        do_write(recv_data.size());
      }
      else
          write_protocol(SERVER + error.message(), PROTOCOL_FILE);
    });
}

/// ==================================================================================
void TcpConnection::do_write(const int& message)
{
  auto self(shared_from_this());

  boost::asio::async_write(m_socket, boost::asio::buffer(&message, sizeof(message)),
    [this, self](const boost::system::error_code& error, size_t bytes_transferred)
    {
      if (!error)
        do_read();
      else
        if (error != boost::asio::error::broken_pipe)
          write_protocol(SERVER + error.message(), PROTOCOL_FILE);
    });
}

/// ==================================================================================
// parses string to vector of Data structures
std::vector<Data> TcpConnection::parse_data(const std::string& data)
{
  std::vector<Data> result;
  std::istringstream is(data);
  std::string line;

  while (std::getline(is, line))
  {
    if (line.empty())
      break;

    size_t comma_pos1 = line.find(',');

    Data data;

    data.date_time = line.substr(0, comma_pos1);
    size_t comma_pos2 = line.find(',', comma_pos1 + 1);
    data.first_column = std::stod(line.substr(comma_pos1 + 1, comma_pos2 - comma_pos1 - 1));
    data.second_column = std::stod(line.substr(comma_pos2 + 1));

    result.push_back(data);
  }

  return result;
}

/// ==================================================================================
// returns the max date and result of division corresponding numbers
std::pair<std::string, double> TcpConnection::calc_data(std::vector<Data>& data_vec)
{
  // find maximum datetime
  boost::posix_time::ptime max_d = boost::posix_time::min_date_time;
  double operand1, operand2;
  
  operand1 = data_vec[0].first_column;
  operand2 = data_vec[0].second_column;

  for (const Data& d : data_vec)
  {
    boost::posix_time::ptime pt = from_string_to_ptime(d.date_time);
    if (max_d < pt)
    {
      max_d = pt;
      operand1 = d.first_column;
      operand2 = d.second_column;
    }
  }
  std::string mdt = from_ptime_to_string(max_d);

  return std::make_pair(mdt, (operand1 / operand2));
}
