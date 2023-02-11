#pragma once

// boost
#include <boost/date_time/posix_time/posix_time.hpp>

/// ==================================================================================
// converts formatted string to ptime
boost::posix_time::ptime from_string_to_ptime(const std::string& str)
{
  std::istringstream is(str);
  is.imbue(std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%d.%m.%Y %H:%M:%S")));
  boost::posix_time::ptime pt;
  is >> pt;

  return pt;
}

// converts ptime to string
std::string from_ptime_to_string(const boost::posix_time::ptime& pt)
{
  std::ostringstream os;
  os.imbue(std::locale(std::locale::classic(), new boost::posix_time::time_facet("%d.%m.%Y %H:%M:%S")));
  os << pt;

  return os.str();
}

void erase_from_symbol(std::string& s, const char& c)
{
  size_t pos = s.find(c);
  if (pos != std::string::npos)
    s = s.substr(0, pos);
}

/// ===================================================================================