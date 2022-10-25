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

template <typename T> struct MessageHeader {
    T id{};
    std::size_t size = 0;

    friend class boost::serialization::access;
    template <class Archive> void serialize(Archive &ar, const unsigned int version)
    {
        ar &id;
        ar &size;
        (void)version;
    }
};
