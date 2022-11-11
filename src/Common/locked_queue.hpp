/**
 * @file locked_queue.hpp
 * @author Tanguy Bellicha (tanguy.bellicha@epitech.eu)
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

/**
 * @brief Locked queue class containing all messages infos
 *
 * @tparam T Type of the values to act on in queue
 */
template <typename T> class LockedQueue {
  private:
    boost::mutex mutex;
    std::queue<T> queue;

  public:
    /**
     * @brief Push information to queue
     *
     * @param value information to push
     */
    void push(T value)
    {
        boost::mutex::scoped_lock lock(mutex);
        queue.push(value);
    };

    /**
     * @brief Pop information of queue
     *
     * @return information to process
     */
    T pop()
    {
        boost::mutex::scoped_lock lock(mutex);
        T value;
        std::swap(value, queue.front());
        queue.pop();
        return value;
    };

    /**
     * @brief Gets if the queue is empty
     *
     * @return True if it is. False if it isn't
     */
    bool empty()
    {
        boost::mutex::scoped_lock lock(mutex);
        return queue.empty();
    }
};
