#include "Tile.h"
#include "Toolbox.h"
#include "GameState.h"
#include <iostream>

Tile::Tile(sf::Vector2f position) {
    this->position = position;
    sprite.setTexture(toolbox->tileHiddenTexture);
    sprite.setPosition(position);
    numberImg.setPosition(position);
    mineOrFlagImg.setPosition(position);
}

void Tile::onClickLeft() {
    if (state == State::REVEALED or state == State::FLAGGED) //do nothing when revealed or flagged tile clicked
        return;
    if (getMine() == 1){ //if there's a mine, explode
        setState(State::EXPLODED);
        gameState.setPlayStatus(GameState::PlayStatus::LOSS);
    }
    else { //it's a hidden tile
        //get coordinates of tile in board
        int xCoord = getLocation().x / 32;
        int yCoord = getLocation().y / 32;

        //assign neighbors, but take into account corners and edges
        std::array<Tile*, 8> tempNeighbors;
        tempNeighbors[0] = (yCoord != 0 && xCoord != 0) ? &gameState.getTileGrid()[(yCoord - 1) * gameState.getWidth() + (xCoord - 1)] : nullptr;
        tempNeighbors[1] = (yCoord != 0) ? &gameState.getTileGrid()[(yCoord - 1) * gameState.getWidth() + (xCoord)] : nullptr;
        tempNeighbors[2] = (yCoord != 0 && xCoord != gameState.getWidth()-1) ? &gameState.getTileGrid()[(yCoord - 1) * gameState.getWidth() + (xCoord + 1)] : nullptr;
        tempNeighbors[3] = (xCoord != 0) ? &gameState.getTileGrid()[(yCoord) * gameState.getWidth() + (xCoord - 1)] : nullptr;
        tempNeighbors[4] = (xCoord != gameState.getWidth()-1) ? &gameState.getTileGrid()[(yCoord) * gameState.getWidth() + (xCoord + 1)] : nullptr;
        tempNeighbors[5] = (yCoord != gameState.getHeight()-1 && xCoord != 0) ? &gameState.getTileGrid()[(yCoord + 1) * gameState.getWidth() + (xCoord - 1)] : nullptr;
        tempNeighbors[6] = (yCoord != gameState.getHeight()-1) ? &gameState.getTileGrid()[(yCoord + 1) * gameState.getWidth() + (xCoord)] : nullptr;
        tempNeighbors[7] = (yCoord != gameState.getHeight()-1 && xCoord != gameState.getWidth()-1) ? &gameState.getTileGrid()[(yCoord + 1) * gameState.getWidth() + (xCoord + 1)] : nullptr;
        setNeighbors(tempNeighbors);

        setState(State::REVEALED);
        if (getSurroundingSum() == 0) { //mine isn't in neighbors, so reveal them
            revealNeighbors();
        }
        bool victory = true; //assume game won
        for (int i = 0; i < gameState.getTileGrid().size(); i++) {
            if ((gameState.getTileGrid()[i].getState() == Tile::State::HIDDEN || gameState.getTileGrid()[i].getState() == Tile::State::FLAGGED) && gameState.getTileGrid()[i].getMine() == 0) {
                victory = false; //if any hidden/flagged tile that does not contain a mine is encountered, game not won
                break;
            }
        }
        if (victory)
            gameState.setPlayStatus(GameState::PlayStatus::WIN); //win
    }
}

void Tile::onClickRight() {
    if (state == State::FLAGGED) {
        setState(State::HIDDEN);
        gameState.removeFlag(); //remove flag when flagged tile right-clicked
    }
    else if (state == State::HIDDEN) {
        setState(State::FLAGGED);
        gameState.placeFlag(); //place flag when hidden tile right-clicked
    }
}

void Tile::revealNeighbors() {
    for (int i = 0; i < 8; i++) {
        if (neighbors[i] != nullptr)
            neighbors[i]->onClickLeft(); //click all the neighboring tiles
    }
}

int Tile::getSurroundingSum() { //returns number of mines surrounding a tile
    int isMineSum = 0;
    for (int i = 0; i < 8; i++)
        if (neighbors[i] != nullptr)
            isMineSum += neighbors[i]->getMine();
    return isMineSum;
}

void Tile::setState(State _state) { //set state and update texture
    state = _state;
    if (state == State::FLAGGED) {
        sprite.setTexture(toolbox->tileHiddenTexture);
        mineOrFlagImg.setTexture(toolbox->tileFlaggedTexture);
    }
    else if (state == State::HIDDEN) {
        sprite.setTexture(toolbox->tileHiddenTexture);
    }
    else if (state == State::REVEALED) {
        sprite.setTexture(toolbox->tileRevealedTexture);
        int sum_ = getSurroundingSum();
        switch (sum_) {
            case 1:
                numberImg.setTexture(toolbox->number1);
                break;
            case 2:
                numberImg.setTexture(toolbox->number2);
                break;
            case 3:
                numberImg.setTexture(toolbox->number3);
                break;
            case 4:
                numberImg.setTexture(toolbox->number4);
                break;
            case 5:
                numberImg.setTexture(toolbox->number5);
                break;
            case 6:
                numberImg.setTexture(toolbox->number6);
                break;
            case 7:
                numberImg.setTexture(toolbox->number7);
                break;
            case 8:
                numberImg.setTexture(toolbox->number8);
                break;
        }
    }
    else if (state == State::EXPLODED) {
        sprite.setTexture(toolbox->tileHiddenTexture);
        mineOrFlagImg.setTexture(toolbox->tileExplodedTexture);
    }
}