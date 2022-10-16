#pragma once

#include <cstddef>
#include <cstring>
#include <vector>
#include "MessageHeader.h"
#include "MessageType.h"

template <typename T> struct Message {
    MessageHeader<T> header;
    std::vector<unsigned char> body;

    std::size_t size() const
    {
        return body.size();
    }

    template <typename ContentType> friend Message<T> &operator<<(Message<T> m, const ContentType &content)
    {
        static_assert(std::is_standard_layout<ContentType>::value, "Not standard layout : Can't push into vector");

        std::size_t currentSize = m.body.size();

        m.body.resize(currentSize + sizeof(ContentType));

        std::memcpy(m.body.data() + currentSize, &content, sizeof(ContentType));

        m.header.size = m.size();

        return m;
    }

    template <typename ContentType> friend Message<T> &operator>>(Message<T> m, const ContentType &content)
    {
        static_assert(std::is_standard_layout<ContentType>::value, "Not standard layout : Can't retreive from vector");

        std::size_t finalSize = m.body.size() - sizeof(ContentType);

        m.body.resize(finalSize);

        std::memcpy(&content, m.body.data() + finalSize, sizeof(ContentType));

        m.header.size = m.size();

        return m;
    }
};
