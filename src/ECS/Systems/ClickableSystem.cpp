/**
 * @file ClickableSystem.cpp
 * @author Cédric Corge (cedric.corge@epitech.eu)
 * @brief
 * @version 0.1
 * @date 2022-11-03
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../Components/AllComponents.hpp"
#include "../World.hpp"

/**
 * @brief Check if the positions intersects
 *
 * @param click_pos Position of the click
 * @param draw Drawn component
 * @param position position of the component to check
 * @return True if there is an intersection
 */
bool pos_intersects(Vector2i click_pos, DrawableComponent draw, PositionComponent position)
{
    if ((click_pos.x >= position.pos.x && click_pos.x <= (position.pos.x + (draw.rect.x_size * draw.scale.x)))
        && (click_pos.y >= position.pos.y && click_pos.y <= (position.pos.y + (draw.rect.y_size * draw.scale.y)))) {
        return (true);
    }
    return (false);
}

int clickable_system(
    World &world, Vector2i click_pos, SceneScreen &current_screen, NetworkClient &client, float &volume)
{
    auto &drawables = world.getRegistry().get_components<DrawableComponent>();
    auto &positions = world.getRegistry().get_components<PositionComponent>();
    auto &clickables = world.getRegistry().get_components<ClickableComponent>();

    for (size_t i = 0; i < clickables.size(); ++i) {
        auto &clickable = clickables[i];
        if (clickable && clickable.has_value()) {
            if (pos_intersects(click_pos, drawables[i].value(), positions[i].value()) == true) {
                (clickable->callback)(world, current_screen, client, volume);
                return (1);
            }
        }
    }
    return (0);
}
