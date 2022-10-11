#include "../registry.h"
#include "../Components/DrawableComponent.h"
#include "../Components/ShapeComponent.hpp"
#include "../Components/PositionComponent.h"
#include "../RessourcesManager.hpp"

int drawable_system(registry &r, sf::RenderWindow &window, RessourcesManager manager)
{
    sparse_array<DrawableComponent> &drawable = r.get_components<DrawableComponent>();
    sparse_array<ShapeComponent> &shape = r.get_components<ShapeComponent>();
    sparse_array<PositionComponent> &position = r.get_components<PositionComponent>();
    std::size_t index = 0;
    sf::Sprite sprite;
    sf::Texture texture;

	for (auto &i : drawable) {
        if (i && i.has_value()) {
            sf::Vector2f vec(position[index]->x, position[index]->y);
            texture = manager.get_texture(i->path);
            if (!(i->rect.x == 0 && i->rect.y == 0 && i->rect.x_size == 0 && i->rect.y_size == 0))
                sprite.setTextureRect(sf::IntRect(i->rect.x, i->rect.y, i->rect.x_size, i->rect.y_size));
            sprite.setTexture(texture);
            sprite.setPosition(vec);
            sprite.setScale(i->x_scale, i->y_scale);
            window.draw(sprite);
		}
        index++;
	}
    index = 0;
    for (size_t i = 0; i < shape.size(); ++i) {
        auto &entity = shape[i];
        //std::cout << "size " << shape.size() << std::endl;
        if (entity.has_value()) {
            //std::cout << "index " << i << std::endl;
            if (entity->type == shape_type::RECTANGLE) {
                sf::RectangleShape rect(sf::Vector2f(entity->length, entity->width));
                rect.setPosition(position[index]->x, position[index]->y);
                rect.setFillColor(sf::Color::Red);
                window.draw(rect);
                break;
            }
            if (entity->type == shape_type::TRIANGLE) {
                sf::CircleShape tri(entity->radius, 3);
                tri.setPosition(position[index]->x, position[index]->y);
                tri.setFillColor(sf::Color::Blue);
                window.draw(tri);
                break;
            }
            if (entity->type == shape_type::CIRCLE) {
                sf::CircleShape circle(entity->radius);
                circle.setPosition(position[index]->x, position[index]->y);
                circle.setFillColor(sf::Color::Blue);
                window.draw(circle);
                break;
            }
            if (entity->type == shape_type::TEXT) {
                sf::Font font(manager.get_font(entity->font));
                sf::Text text;

                text.setCharacterSize(entity->font_size);
                text.setFont(font);
                text.setPosition(position[index]->x, position[index]->y);
                text.setString(entity->text);
                text.setFillColor(sf::Color::Black);
                window.draw(text);
            }
        }
        index++;
    }
    return (0);
}