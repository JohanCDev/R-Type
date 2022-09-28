#include <string>
#include "utils.hpp"

std::string send_packet(size_t type, std::string content)
{
    char c_type[1];
    char length[1];
    std::string result;

    push_back_byte(c_type, type);
    push_back_byte(length, content.size());
    result.append(c_type);
    result.append(length);
    result.pop_back();
    result.append(content);
    return result;
}