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

/**
 * @brief array class with optional elements
 *
 * @tparam Component
 */
template <typename Component> class sparse_array {
  public:
    /**
     * @brief Contains the Component if there is one
     *
     */
    using value_type = std::optional<Component>;

    /**
     * @brief Contains a reference to the type of the component
     *
     */
    using reference_type = value_type &;

    /**
     * @brief Contains a const reference to the type of the component
     *
     */
    using const_reference_type = value_type const &;

    /**
     * @brief Contains a vector of the types of the component if there is one
     *
     */
    using container_t = std::vector<value_type>;

    /**
     * @brief Containes the size type of the container
     *
     */
    using size_type = typename container_t::size_type;

    /**
     * @brief Iterator to move in the container
     *
     */
    using iterator = typename container_t::iterator;

    /**
     * @brief Const iterator to move in the container
     *
     */
    using const_iterator = typename container_t::const_iterator;

  public:
    /**
     * @brief Construct a new sparse array object
     *
     */
    sparse_array() = default;

    /**
     * @brief Copy a new sparse array object
     *
     */
    sparse_array(sparse_array const &) = default;

    /**
     * @brief Move a new sparse array object
     *
     */
    sparse_array(sparse_array &&) noexcept = default;

    /**
     * @brief Destroy the sparse array object
     *
     */
    ~sparse_array() = default;

    /**
     * @brief Initialize new sparse array
     *
     * @return sparse_array&
     */
    sparse_array &operator=(sparse_array const &) = default;

    /**
     * @brief Initialize new sparse array
     *
     * @return sparse_array&
     */
    sparse_array &operator=(sparse_array &&) noexcept = default;

    /**
     * @brief Get an element in the array
     *
     * @param idx
     * @return reference_type
     */
    reference_type operator[](size_t idx)
    {
        return _data[idx];
    };

    /**
     * @brief Get an constant element in the array
     *
     * @param idx
     * @return const_reference_type
     */
    const_reference_type operator[](size_t idx) const
    {
        return _data[idx];
    };

    /**
     * @brief Get a iterator to the first element
     *
     * @return iterator
     */
    iterator begin()
    {
        return _data.begin();
    };

    /**
     * @brief Get a constant iterator to the first element
     *
     * @return const_iterator
     */
    const_iterator begin() const
    {
        return _data.begin();
    };

    /**
     * @brief Get a constant iterator to the first element
     *
     * @return const_iterator
     */
    const_iterator cbegin() const
    {
        return _data.cbegin();
    };

    /**
     * @brief Get a iterator to the last element
     *
     * @return iterator
     */
    iterator end()
    {
        return _data.end();
    };

    /**
     * @brief Get a constant iterator to the last element
     *
     * @return const_iterator
     */
    const_iterator end() const
    {
        return _data.end();
    };

    /**
     * @brief Get a constant iterator to the last element
     *
     * @return const_iterator
     */
    const_iterator cend() const
    {
        return _data.cend();
    };

    /**
     * @brief Get the size of the sparse array
     *
     * @return size_type
     */
    size_type size() const
    {
        return _data.size();
    };

    /**
     * @brief Insert an element into the sparse array
     *
     * @param pos
     * @param c
     * @return reference_type
     */
    reference_type insert_at(size_type pos, Component const &c)
    {
        this->grow_to(pos);
        _data.at(pos) = c;
        return _data.at(pos);
    }

    /**
     * @brief Insert an element into the sparse array
     *
     * @param pos
     * @param c
     * @return reference_type
     */
    reference_type insert_at(size_type pos, Component &&c)
    {
        this->grow_to(pos);
        _data.at(pos) = c;
        return _data.at(pos);
    }

    /**
     * @brief Build and insert an element into the sparse array
     *
     * @tparam Params
     * @param pos
     * @param args
     * @return reference_type
     */
    template <class... Params> reference_type emplace_at(size_type pos, Params &&...args)
    {
        Component c(args...);

        return this->insert_at(pos, c);
    }

    /**
     * @brief Erase an element of the sparse array
     *
     * @param pos
     */
    void erase(size_type pos)
    {
        if (this->size() > pos) {
            _data.at(pos) = value_type();
        }
    }

    /**
     * @brief Get the index object
     *
     * @param c
     * @return size_type
     */
    size_type get_index(value_type const &c) const
    {
        auto begin = this->begin();
        auto it = std::find(begin, this->end(), c);
        if (it != this->end()) {
            return std::distance(begin, it);
        }
        return 0;
    }

    /**
     * @brief Initialize space into sparse array
     *
     * @param pos
     */
    void grow_to(size_type pos)
    {
        while (this->size() < pos + 1) {
            _data.push_back(value_type());
        }
    }

    /**
     * @brief Get a constant reference to the last element of the sparse array
     *
     * @return const_reference_type
     */
    const_reference_type back() const
    {
        return _data.back();
    }

  private:
    container_t _data;
};
