#pragma once

#include <SFML/Graphics.hpp>
#include <array>


class Tile {
public:
    enum State {REVEALED, HIDDEN, FLAGGED, EXPLODED};
private:
    sf::Vector2f position;
    State state = State::HIDDEN;
    std::array<Tile*, 8> neighbors;
    int isMine;
    sf::Sprite sprite;
    sf::Sprite numberImg;
    sf::Sprite mineOrFlagImg;
    int getSurroundingSum();
public:
    Tile(sf::Vector2f position);
    sf::Vector2f getLocation() {return position;}
    std::array<Tile*, 8>& getNeighbors() {return neighbors;}
    void setState(State _state);
    State getState() {return state;}
    void setNeighbors(std::array<Tile*, 8> _neighbors) {neighbors = _neighbors;}
    void onClickLeft();
    void onClickRight();
    int getMine() {return isMine;}
    void setMine(int mine) {isMine = mine;}
    sf::Sprite& getSprite() {return sprite;}
    sf::Sprite& getNumberImg() {return numberImg;}
    sf::Sprite& getMineOrFlagImg() {return mineOrFlagImg;}
protected:
    void revealNeighbors();
};
