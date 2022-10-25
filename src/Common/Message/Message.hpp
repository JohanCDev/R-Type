/**
 * @file Message.hpp
 * @author Tanguy Bellicha (tanguy.bellicha@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include <cstddef>
#include <cstring>
#include <string>
#include <vector>
#include "MessageHeader.hpp"
#include "MessageType.hpp"

#include <iostream>
template <typename T> struct Message {
    MessageHeader<T> header;
    std::vector<uint8_t> body;

    std::size_t size() const
    {
        return body.size();
    }

    template <typename ContentType> friend Message<T> &operator<<(Message<T> &m, ContentType &content)
    {
        static_assert(std::is_standard_layout<ContentType>::value, "Not standard layout : Can't push into vector");

        std::size_t currentSize = m.body.size();

        m.body.resize(currentSize + sizeof(ContentType));

        std::memcpy(m.body.data() + currentSize, &content, sizeof(ContentType));

        m.header.size = m.size();

        return m;
    }

    template <typename ContentType> friend Message<T> &operator>>(Message<T> &m, ContentType &content)
    {
        static_assert(std::is_standard_layout<ContentType>::value, "Not standard layout : Can't retreive from vector");

        std::size_t finalSize = m.body.size() - sizeof(ContentType);

        m.body.resize(finalSize);

        std::memcpy(&content, m.body.data() + finalSize, sizeof(ContentType));

        m.header.size = m.size();

        return m;
    }

    friend class boost::serialization::access;
    template <class Archive> void serialize(Archive &ar, const unsigned int version)
    {
        ar &header;
        ar &body;
        (void)version;
    }
};
