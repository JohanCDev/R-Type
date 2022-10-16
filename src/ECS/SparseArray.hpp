/**
 * @file SparseArray.hpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <optional>
#include <vector>

template <typename Component> // You can also mirror the definition of std :: vector, that takes an additional allocator
                              // .
class sparse_array {
  public:
    using value_type = std::optional<Component>; // optional component type
    using reference_type = value_type &;
    using const_reference_type = value_type const &;
    using container_t = std::vector<value_type>; // optionally add your allocator template here .
    using size_type = typename container_t::size_type;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;

  public:
    sparse_array() = default;                         // You can add more constructors .
    sparse_array(sparse_array const &) = default;     // copy constructor
    sparse_array(sparse_array &&) noexcept = default; // move constructor
    ~sparse_array() = default;
    sparse_array &operator=(sparse_array const &) = default;     // copy assignment operator
    sparse_array &operator=(sparse_array &&) noexcept = default; // move assignment operator
    reference_type operator[](size_t idx)
    {
        return _data[idx];
    };
    const_reference_type operator[](size_t idx) const
    {
        return _data[idx];
    };
    iterator begin()
    {
        return _data.begin();
    };
    const_iterator begin() const
    {
        return _data.begin();
    };
    const_iterator cbegin() const
    {
        return _data.cbegin();
    };
    iterator end()
    {
        return _data.end();
    };
    const_iterator end() const
    {
        return _data.end();
    };
    const_iterator cend() const
    {
        return _data.cend();
    };
    size_type size() const
    {
        return _data.size();
    };
    reference_type insert_at(size_type pos, Component const &c)
    {
        this->grow_to(pos);
        _data.at(pos) = c;
        return _data.at(pos);
    }
    reference_type insert_at(size_type pos, Component &&c)
    {
        this->grow_to(pos);
        _data.at(pos) = c;
        return _data.at(pos);
    }
    template <class... Params> reference_type emplace_at(size_type pos, Params &&...args)
    {
        Component c(args...);

        return this->insert_at(pos, c);
    }

    void erase(size_type pos)
    {
        if (this->size() > pos) {
            _data.at(pos) = value_type();
        }
    }

    size_type get_index(value_type const &c) const
    {
        auto begin = this->begin();
        auto it = std::find(begin, this->end(), c);
        if (it != this->end()) {
            return std::distance(begin, it);
        }
        return 0;
    }

    void grow_to(size_type pos)
    {
        while (this->size() < pos + 1) {
            _data.push_back(value_type());
        }
    }
    const_reference_type back() const
    {
        return _data.back();
    }

  private:
    container_t _data;
};
