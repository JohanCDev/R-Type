/**
 * @file Entity.hpp
 * @author Tanguy Bellicha (tanguy.bellicha@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-10-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

class Entity {
  public:
    // Constructor should be private
    explicit Entity(size_t entity_id) : id(entity_id){};

    friend class registry;
    size_t id;

    operator size_t() const
    {
        return id;
    };
};
