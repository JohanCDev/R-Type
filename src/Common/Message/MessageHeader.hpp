/**
 * @file MessageHeader.hpp
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

/**
 * @brief Struct containing the message header
 *
 * @tparam T Type of the message
 */
template <typename T> struct MessageHeader {
    /**
     * @brief Id of the message
     *
     */
    T id{};

    /**
     * @brief Size of the message
     *
     */
    std::size_t size = 0;

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
         * @brief ID of the archive
         *
         */
        ar &id;

        /**
         * @brief Size of the archive
         *
         */
        ar &size;

        /**
         * @brief Version
         *
         */
        (void)version;
    }
};
