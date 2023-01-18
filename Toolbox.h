#pragma once

#include "Button.h"
#include "Tile.h"

class Toolbox {
private:
    static Toolbox* instance;
    Toolbox();
    ~Toolbox();
public:
    sf::RenderWindow window;
    Button* debugButton;
    Button* newGameButton;
    Button* testButton1;
    Button* testButton2;
    static Toolbox* getInstance();

    sf::Texture newGameTexture;
    sf::Texture lossTexture;
    sf::Texture winTexture;
    sf::Texture debugTexture;
    sf::Texture test1Texture;
    sf::Texture test2Texture;
    sf::Texture digitTexture;
    sf::Texture tileHiddenTexture;
    sf::Texture tileRevealedTexture;
    sf::Texture tileFlaggedTexture;
    sf::Texture tileExplodedTexture;
    sf::Texture number1;
    sf::Texture number2;
    sf::Texture number3;
    sf::Texture number4;
    sf::Texture number5;
    sf::Texture number6;
    sf::Texture number7;
    sf::Texture number8;
    sf::Sprite digit1Sprite, digit2Sprite, digit3Sprite;
    sf::RectangleShape whiteRect;
    bool debug = false;
    bool loaded = false;
    bool hideMines = false;

    std::vector<Tile> tileGrid;

};

extern Toolbox* toolbox;