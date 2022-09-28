#include <cstdio>
#include <stdint.h>

size_t encode_to_byte(void *output, uint32_t input)
{
    uint8_t byte;
    uint8_t *o = (uint8_t *)output;

    do {
        byte = input & 0x7f;
        input >>= 7;
        if (input != 0)
            byte |= 0x80;
        *(o++) = byte;
    } while (input != 0);
    return (size_t)(o - (uint8_t *)output);
}

size_t push_back_byte(char buffer[], uint32_t value)
{
    uint8_t tmp[1];
    size_t size = encode_to_byte(tmp, value);

    for (size_t i = 0; i < size; i++)
        buffer[i] = tmp[i];
    return size;
}