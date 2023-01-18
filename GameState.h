#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

#include "Tile.h"

class GameState {
public:
    enum PlayStatus {WIN, LOSS, PLAYING};
private:
    PlayStatus playStatus;
    int mineCount, flagCount, gameWidth, gameHeight;
    std::vector<Tile> tileGrid;


public:
    GameState(sf::Vector2i _dimensions = sf::Vector2i(25, 16), int _numberOfMines = 50);
    GameState(const char* filepath);
    int getFlagCount() {return flagCount;}
    int getMineCount() {return mineCount;}
    Tile* getTile(int x, int y);
    PlayStatus getPlayStatus() {return playStatus;}
    void setPlayStatus(PlayStatus _status) {playStatus = _status;}

    void placeFlag() {mineCount -= 1;}
    void removeFlag() {mineCount += 1;}
    std::vector<Tile>& getTileGrid() {return tileGrid;}
    int getWidth() {return gameWidth;}
    int getHeight() {return gameHeight;}

};

extern GameState gameState;
