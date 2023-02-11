#pragma once

// std
#include <string>

void write_protocol(const std::pair<std::string, double>& info, const char* protocol_file);
void write_protocol(const int& info, const char* protocol_file);
void write_protocol(const std::string& info, const char* protocol_file);