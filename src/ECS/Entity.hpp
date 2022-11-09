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

/**
 * @brief Entity class
 *
 */
class Entity {
  public:
    /**
     * @brief Construct a new Entity object
     *
     * @param entity_id ID of the entity
     */
    explicit Entity(size_t entity_id) : id(entity_id){};

    friend class registry;

    /**
     * @brief Store entity's ID
     *
     */
    size_t id;

    /**
     * @brief Return the id of the entity
     *
     * @return ID as a size_t
     */
    operator size_t() const
    {
        return id;
    };
};
