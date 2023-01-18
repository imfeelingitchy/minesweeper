#pragma once

#include <functional>
#include <SFML/Graphics.hpp>

class Button {
    sf::Vector2f position;
    sf::Sprite* sprite;
public:
    Button(sf::Vector2f _position, std::function<void(void)> _onClick);
    ~Button();
    sf::Vector2f getPosition() {return position;}
    sf::Sprite* getSprite() {return sprite;}
    void setSprite(sf::Sprite* _sprite) {sprite = _sprite;}
    std::function<void(void)> onClick;
};
