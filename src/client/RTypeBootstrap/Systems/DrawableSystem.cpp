#include "../registry.h"
#include "../Components/DrawableComponent.h"
#include "../Components/ShapeComponent.hpp"
#include "../Components/PositionComponent.h"
#include "../AssetsManager.hpp"
#include <iostream>

int drawable_system(registry &r, sf::RenderWindow &window, AssetsManager manager)
{
    sparse_array<DrawableComponent> &drawable = r.get_components<DrawableComponent>();
    sparse_array<ShapeComponent> &shape = r.get_components<ShapeComponent>();
    sparse_array<PositionComponent> &position = r.get_components<PositionComponent>();
    std::size_t index = 0;
    sf::Sprite sprite;
    sf::Texture texture;

	for (auto &i : drawable) {
        if (i && i.has_value() && !shape[index]) {
            sf::Vector2f vec(position[index]->x, position[index]->y);
            texture = manager.get_texture(i->path);
            sprite.setTexture(texture);
            sprite.setPosition(vec);
            sprite.setScale(i->x_scale, i->y_scale);
            window.draw(sprite);
		}
        index++;
	}
    index = 0;
    for (auto &entity : shape) {
        if (entity && entity.has_value()) {
            if (entity->type == shape_type::RECTANGLE) {
                sf::RectangleShape rect(sf::Vector2f(entity->length, entity->width));
                rect.setPosition(position[index]->x, position[index]->y);
                rect.setFillColor(sf::Color::Red);
                window.draw(rect);
                break;
            }
        }
        index++;
    }
    return (0);
}