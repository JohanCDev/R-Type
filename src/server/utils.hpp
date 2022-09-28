#pragma once

#include <string>

std::string create_packet(size_t type, std::string content);
void stream2hex(const std::string str, std::string &hexstr, bool capital = false);
size_t encode_to_byte(void *output, uint32_t input);
size_t push_back_byte(char buffer[], uint32_t value);