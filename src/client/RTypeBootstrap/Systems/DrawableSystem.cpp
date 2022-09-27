#include "../registry.h"
#include "../Components/DrawableComponent.h"
#include "../Components/PositionComponent.h"
#include "../AssetsManager.hpp"

int drawable_system(registry &r, sf::RenderWindow &window, AssetsManager manager)
{
    sparse_array<DrawableComponent> &drawable = r.get_components<DrawableComponent>();
    sparse_array<PositionComponent> &position = r.get_components<PositionComponent>();
    std::size_t index = 0;
    sf::Sprite sprite;
    sf::Texture texture;

	for (auto &i : drawable) {
        if (i && i.has_value()) {
            sf::Vector2f vec(position[index]->x, position[index]->y);
            texture = manager.get_texture(i->path);
            sprite.setTexture(texture);
            sprite.setPosition(vec);
            sprite.setScale(i->x_scale, i->y_scale);
            window.draw(sprite);
		}
        index++;
	}
    return (0);
}