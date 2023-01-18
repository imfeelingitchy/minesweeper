#include <iostream>
#include <SFML/Graphics.hpp>
#include <array>

#include "Tile.h"
#include "Button.h"
#include "GameState.h"
#include "Toolbox.h"
#include "minesweeper.h"

int launch() {
    //load all textures
    toolbox->newGameTexture.loadFromFile("./images/face_happy.png");
    toolbox->winTexture.loadFromFile("./images/face_win.png");
    toolbox->lossTexture.loadFromFile("./images/face_lose.png");
    toolbox->debugTexture.loadFromFile("./images/debug.png");
    toolbox->test1Texture.loadFromFile("./images/test_1.png");
    toolbox->test2Texture.loadFromFile("./images/test_2.png");
    toolbox->digitTexture.loadFromFile("./images/digits.png");
    toolbox->tileHiddenTexture.loadFromFile("./images/tile_hidden.png");
    toolbox->tileRevealedTexture.loadFromFile("./images/tile_revealed.png");
    toolbox->tileFlaggedTexture.loadFromFile("./images/flag.png");
    toolbox->tileExplodedTexture.loadFromFile("./images/mine.png");
    toolbox->number1.loadFromFile("./images/number_1.png");
    toolbox->number2.loadFromFile("./images/number_2.png");
    toolbox->number3.loadFromFile("./images/number_3.png");
    toolbox->number4.loadFromFile("./images/number_4.png");
    toolbox->number5.loadFromFile("./images/number_5.png");
    toolbox->number6.loadFromFile("./images/number_6.png");
    toolbox->number7.loadFromFile("./images/number_7.png");
    toolbox->number8.loadFromFile("./images/number_8.png");
    toolbox->whiteRect.setSize(sf::Vector2f(210, 32));
    toolbox->loaded = true;

    //initialize buttons
    toolbox->newGameButton = new Button(sf::Vector2f(400-32, 600-64), restart);
    toolbox->debugButton = new Button(sf::Vector2f(400-32 + 64*2, 600-64), toggleDebugMode);
    toolbox->testButton1 = new Button(sf::Vector2f(400-32 + 64*3, 600-64), testBoard1);
    toolbox->testButton2 = new Button(sf::Vector2f(400-32 + 64*4, 600-64), testBoard2);

    //set button sprites
    toolbox->newGameButton->setSprite(new sf::Sprite(toolbox->newGameTexture));
    toolbox->newGameButton->getSprite()->setPosition(toolbox->newGameButton->getPosition());

    toolbox->debugButton->setSprite(new sf::Sprite(toolbox->debugTexture));
    toolbox->debugButton->getSprite()->setPosition(toolbox->debugButton->getPosition());

    toolbox->testButton1->setSprite(new sf::Sprite(toolbox->test1Texture));
    toolbox->testButton1->getSprite()->setPosition(toolbox->testButton1->getPosition());

    toolbox->testButton2->setSprite(new sf::Sprite(toolbox->test2Texture));
    toolbox->testButton2->getSprite()->setPosition(toolbox->testButton2->getPosition());

    //mine counter digits (white rectangle covers excess area)
    toolbox->digit1Sprite.setPosition(0, 600 - 32);
    toolbox->digit2Sprite.setPosition(21, 600 - 32);
    toolbox->digit3Sprite.setPosition(42, 600 - 32);
    toolbox->digit1Sprite.setTexture(toolbox->digitTexture);
    toolbox->digit2Sprite.setTexture(toolbox->digitTexture);
    toolbox->digit3Sprite.setTexture(toolbox->digitTexture);
    toolbox->whiteRect.setFillColor(sf::Color(255, 255, 255));
    toolbox->whiteRect.setPosition(sf::Vector2f(21 * 3, 600 - 32));

    toolbox->window.create(sf::VideoMode(800, 600), "P4 - Minesweeper, Rithik Raja");

    restart();
    gameLoop();

    return 0;
}

void render() {
    //draw buttons
    toolbox->window.draw(*toolbox->newGameButton->getSprite());
    toolbox->window.draw(*toolbox->debugButton->getSprite());
    toolbox->window.draw(*toolbox->testButton1->getSprite());
    toolbox->window.draw(*toolbox->testButton2->getSprite());

    //draw digits
    toolbox->window.draw(toolbox->digit1Sprite);
    toolbox->window.draw(toolbox->digit2Sprite);
    toolbox->window.draw(toolbox->digit3Sprite);
    toolbox->window.draw(toolbox->whiteRect);

    for (int i = 0; i < gameState.getTileGrid().size(); i++) {
        if (gameState.getTileGrid()[i].getMine() == 1) {
            if (getDebugMode() == true || gameState.getPlayStatus() == GameState::PlayStatus::LOSS)
                gameState.getTileGrid()[i].setState(Tile::State::EXPLODED); //show mines if in debug mode or game lost
            else if (gameState.getPlayStatus() == GameState::PlayStatus::WIN) {
                gameState.getTileGrid()[i].setState(Tile::State::FLAGGED); //show flags if game won
            }
            else {
                if (toolbox->hideMines) {
                    gameState.getTileGrid()[i].setState(Tile::State::HIDDEN); //hide mines when debug mode turned off
                }
            }
        }
        toolbox->window.draw(gameState.getTileGrid()[i].getSprite()); //draw tiles
        toolbox->window.draw(gameState.getTileGrid()[i].getNumberImg()); //draw numbers on tiles
        if (gameState.getTileGrid()[i].getState() == Tile::State::FLAGGED || gameState.getTileGrid()[i].getState() == Tile::State::EXPLODED)
            toolbox->window.draw(gameState.getTileGrid()[i].getMineOrFlagImg()); //draw flags

    }
    toolbox->hideMines = false;
}

void restart() {
    gameState = GameState();
}

void toggleDebugMode() {
    toolbox->debug = not toolbox->debug;
    if (!toolbox->debug)
        toolbox->hideMines = true;
}

bool getDebugMode() {
    return toolbox->debug;
}

void testBoard1() {
    gameState = GameState("./boards/testboard1.brd");
}

void testBoard2() {
    gameState = GameState("./boards/testboard2.brd");
}

void gameLoop() {
    sf::Event event;
    int clicked; //0 -> none, 1 -> left, 2 -> right
    auto getMousePos = [&]() {return static_cast<sf::Vector2f>(sf::Mouse::getPosition(toolbox->window));};

    while (toolbox->window.isOpen()) {

        clicked = 0;

        while (toolbox->window.pollEvent(event)) { //check if window closed or mouse clicked
            if (event.type == sf::Event::Closed)
                toolbox->window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    clicked = 1;
                } else if (event.mouseButton.button == sf::Mouse::Right) {
                    clicked = 2;
                }
            }
        }

        if (clicked == 1) { //check if buttons clicked
            if (toolbox->newGameButton->getSprite()->getGlobalBounds().contains(getMousePos()))
                toolbox->newGameButton->onClick();
            else if (toolbox->debugButton->getSprite()->getGlobalBounds().contains(getMousePos()))
                toolbox->debugButton->onClick();
            else if (toolbox->testButton1->getSprite()->getGlobalBounds().contains(getMousePos()))
                toolbox->testButton1->onClick();
            else if (toolbox->testButton2->getSprite()->getGlobalBounds().contains(getMousePos()))
                toolbox->testButton2->onClick();
            else { //check if tile clicked
                if (gameState.getPlayStatus() == GameState::PlayStatus::PLAYING) {
                    for (int i = 0; i < gameState.getTileGrid().size(); i++) {
                        if (gameState.getTileGrid()[i].getSprite().getGlobalBounds().contains(getMousePos())) {
                            gameState.getTileGrid()[i].onClickLeft();
                        }
                    }
                }
            }
        } else if (clicked == 2 && (gameState.getPlayStatus() == GameState::PlayStatus::PLAYING)) { //check if tile right-clicked
            for (int i = 0; i < gameState.getTileGrid().size(); i++) {
                if (gameState.getTileGrid()[i].getSprite().getGlobalBounds().contains(getMousePos())) {
                    gameState.getTileGrid()[i].onClickRight();
                }
            }
        }

        if (gameState.getMineCount() < 0) { //reposition mine counter digit (negative mine count)
            toolbox->digit1Sprite.setTextureRect(sf::IntRect(210, 0, 21, 32));
            toolbox->digit2Sprite.setTextureRect(sf::IntRect(21 * (-gameState.getMineCount() / 10), 0, 21, 32));
            toolbox->digit3Sprite.setTextureRect(sf::IntRect(21 * (-gameState.getMineCount() % 10), 0, 21, 32));
        } else { //reposition mine counter digit (positive mine count)
            toolbox->digit1Sprite.setTextureRect(sf::IntRect(21 * (gameState.getMineCount() / 100), 0, 21, 32));
            toolbox->digit2Sprite.setTextureRect(sf::IntRect(21 * (gameState.getMineCount() / 10 % 10), 0, 21, 32));
            toolbox->digit3Sprite.setTextureRect(sf::IntRect(21 * (gameState.getMineCount() % 10), 0, 21, 32));
        }

        //change texture of smiley
        if (gameState.getPlayStatus() == GameState::PlayStatus::LOSS)
            toolbox->newGameButton->getSprite()->setTexture(toolbox->lossTexture);
        else if (gameState.getPlayStatus() == GameState::PlayStatus::WIN)
            toolbox->newGameButton->getSprite()->setTexture(toolbox->winTexture);
        else
            toolbox->newGameButton->getSprite()->setTexture(toolbox->newGameTexture);

        //draw to screen
        toolbox->window.clear(sf::Color(255, 255, 255));
        render();
        toolbox->window.display();
    }
}

int main() {
    return launch();
}
