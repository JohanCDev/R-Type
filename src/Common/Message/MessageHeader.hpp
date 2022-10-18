/**
 * @file MessageHeader.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-10-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

template <typename T> struct MessageHeader {
    T id{};
    std::size_t size = 0;
};
