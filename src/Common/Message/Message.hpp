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
#include <iostream>
#include <string>
#include <vector>
#include "MessageHeader.hpp"
#include "MessageType.hpp"

/**
 * @brief Message structure
 *
 * @tparam T Type of the message
 */
template <typename T> struct Message {
    /**
     * @brief Contains the header of the message
     *
     */
    MessageHeader<T> header;

    /**
     * @brief Contains the body of the message
     *
     */
    std::vector<uint8_t> body;

    /**
     * @brief Returns the size of message's body
     *
     * @return Size of the message's body
     */
    std::size_t size() const
    {
        return body.size();
    }

    /**
     * @brief Implement the operator <<
     *
     * @tparam ContentType Type of the received content
     * @param m message to process
     * @param content contentType of the message
     * @return Message<T>& Message to process
     */
    template <typename ContentType> friend Message<T> &operator<<(Message<T> &m, const ContentType &content)
    {
        static_assert(std::is_standard_layout<ContentType>::value, "Not standard layout : Can't push into vector");

        std::size_t currentSize = m.body.size();
        m.body.resize(currentSize + sizeof(ContentType));
        std::memcpy(m.body.data() + currentSize, &content, sizeof(ContentType));
        m.header.size = m.size();
        return m;
    }

    /**
     * @brief Implement the operator >>
     *
     * @tparam ContentType Type of the received content
     * @param m message to process
     * @param content contentType of the message
     * @return Message<T>& Message to process
     */
    template <typename ContentType> friend Message<T> &operator>>(Message<T> &m, ContentType &content)
    {
        static_assert(std::is_standard_layout<ContentType>::value, "Not standard layout : Can't retreive from vector");

        std::size_t finalSize = m.body.size() - sizeof(ContentType);
        m.body.resize(finalSize);
        std::memcpy(&content, m.body.data() + finalSize, sizeof(ContentType));
        m.header.size = m.size();
        return m;
    }

    /**
     * @brief Boost class accessing to serialization
     *
     */
    friend class boost::serialization::access;

    /**
     * @brief Class used to serialize
     *
     * @tparam Archive containing the serialized message
     * @param ar The archive to process
     * @param version version of serialization
     */
    template <class Archive> void serialize(Archive &ar, const unsigned int version)
    {
        /**
         * @brief Header of the archive
         *
         */
        ar &header;
        /**
         * @brief Body of the archive
         *
         */
        ar &body;
        /**
         * @brief Version
         *
         */
        (void)version;
    }
};
