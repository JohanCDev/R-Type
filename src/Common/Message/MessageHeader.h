#pragma once

template <typename T> struct MessageHeader {
    T id{};
    std::size_t size = 0;
};