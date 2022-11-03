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

#include "../World.hpp"
#include "../Components/AllComponents.hpp"

bool is_hover(Vector2i click_pos, DrawableComponent draw, PositionComponent position)
{
    if ((click_pos.x >= position.pos.x && click_pos.x <= (position.pos.x + (draw.rect.x_size * draw.scale.x))) &&
        (click_pos.y >= position.pos.y && click_pos.y <= (position.pos.y + (draw.rect.y_size * draw.scale.y)))) {
        return (true);
    }
    return (false);
}

int clickable_system(World &world, Vector2i click_pos, SceneScreen &actual_screen)
{
    auto &drawables = world.getRegistry().get_components<DrawableComponent>();
    auto &positions = world.getRegistry().get_components<PositionComponent>();
    auto &clickables = world.getRegistry().get_components<ClickableComponent>();

    for (size_t i = 0; i < clickables.size(); ++i) {
        auto &clickable = clickables[i];

        if (clickable && clickable.has_value()) {
            if (is_hover(click_pos, drawables[i].value(), positions[i].value()) == true) {
                (clickable->callback)(world, actual_screen);
            }
        }
    }
    return (0);
}