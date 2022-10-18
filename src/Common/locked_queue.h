/**
 * @file locked_queue.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-10-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <boost/thread/mutex.hpp>
#include <list>
#include <queue>

template <typename T> class LockedQueue {
  private:
    boost::mutex mutex;
    std::queue<T> queue;

  public:
    void push(T value)
    {
        boost::mutex::scoped_lock lock(mutex);
        queue.push(value);
    };

    T pop()
    {
        boost::mutex::scoped_lock lock(mutex);
        T value;
        std::swap(value, queue.front());
        queue.pop();
        return value;
    };

    bool empty()
    {
        boost::mutex::scoped_lock lock(mutex);
        return queue.empty();
    }
};
