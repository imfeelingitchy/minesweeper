
#include "Button.h"

Button::Button(sf::Vector2f _position, std::function<void()> _onClick) {
    position = _position;
    onClick = _onClick;
}

Button::~Button() {delete sprite;}