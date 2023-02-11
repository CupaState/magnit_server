// std
#include <iostream>

// posix
#include <sys/file.h>
#include <unistd.h>

// local
#include "file_utils.h"

void write_protocol(const std::pair<std::string, double>& info, const char* protocol_file)
{
  std::string err_msg = "Server: error was occured while trying to";

  int fd = open(protocol_file, O_RDWR | O_CREAT | O_APPEND, 0666);
  if (fd < 0)
    std::cout << err_msg + "open protocol.txt file";

  // Acquire the lock
  int rc = flock(fd, LOCK_EX);
  if (rc != 0)
    std::cout << err_msg + "lock protocol.txt file";
  
  std::string write_data = info.first + " " + std::to_string(info.second) + "\n";
  if (write(fd, write_data.c_str(), write_data.size()) == -1)
    std::cout << err_msg + "write protocol.txt file\n";

  // Release the lock
  rc = flock(fd, LOCK_UN);
  if (rc != 0)
    std::cout << err_msg + "unlock protocol.txt file";
}

void write_protocol(const int& info, const char* protocol_file)
{
  std::string err_msg = "Client: error was occured while trying to";
  int fd = open(protocol_file, O_RDWR | O_CREAT | O_APPEND, 0666);
  if (fd < 0)
    std::cout << err_msg + "open protocol.txt file";
    
  // Acquire the lock
  int rc = flock(fd, LOCK_EX);
  if (rc != 0)
    std::cout << err_msg + "lock protocol.txt file";
  
  std::string write_data = std::to_string(info) + "\n";
  if (write(fd, write_data.c_str(), write_data.size()) == -1)
    std::cout << err_msg + "write protocol.txt file\n";

  // Release the lock
  rc = flock(fd, LOCK_UN);
  if (rc != 0)
    std::cout << err_msg + "unlock protocol.txt file";
}

void write_protocol(const std::string& info, const char* protocol_file)
{
  std::string err_msg = "Client: error was occured while trying to";
  int fd = open(protocol_file, O_RDWR | O_CREAT | O_APPEND, 0666);
  if (fd < 0)
    std::cout << err_msg + "open protocol.txt file";
    
  // Acquire the lock
  int rc = flock(fd, LOCK_EX);
  if (rc != 0)
    std::cout << err_msg + "lock protocol.txt file";
  
  std::string write_data = info + "\n";
  if (write(fd, write_data.c_str(), write_data.size()) == -1)
    std::cout << err_msg + "write protocol.txt file\n";

  // Release the lock
  rc = flock(fd, LOCK_UN);
  if (rc != 0)
    std::cout << err_msg + "unlock protocol.txt file";
}
