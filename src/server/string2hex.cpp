#include <string>

void stream2hex(const std::string str, std::string &hexstr, bool capital = false)
{
    const size_t a = capital ? 'A' - 1 : 'a' - 1;

    hexstr.resize(str.size() * 2);
    for (size_t i = 0, c = str[0] & 0xFF; i < hexstr.size(); c = str[i / 2] & 0xFF) {
        hexstr[i++] = c > 0x9F ? (c / 16 - 9) | a : c / 16 | '0';
        hexstr[i++] = (c & 0xF) > 9 ? (c % 16 - 9) | a : c % 16 | '0';
    }
}