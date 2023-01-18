#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

#include "GameState.h"
#include "Toolbox.h"

GameState::GameState(sf::Vector2i _dimensions, int _numberOfMines) {
    if (!toolbox->loaded) //only proceed if loaded
        return;
    tileGrid.clear();
    playStatus = PlayStatus::PLAYING;
    mineCount = _numberOfMines;
    gameWidth = _dimensions.x;
    gameHeight = _dimensions.y;
    flagCount = 0;
    //create tiles at required positions
    for (int i = 0; i < gameHeight * gameWidth; i++) {
        Tile temp = Tile(sf::Vector2f((i % gameWidth) * 32, (i / gameWidth) * 32));
        tileGrid.push_back(temp);
        }

    std::random_device device;
    std::mt19937 rand(device());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, gameWidth * gameHeight - 1);

    std::vector<int> randNumbers;
    int randNumber;
    while (randNumbers.size() != mineCount) { //get a vector of the required number of random numbers with no repetition
        randNumber = dist(rand);
        if (std::find(randNumbers.begin(), randNumbers.end(), randNumber) == randNumbers.end())
            randNumbers.push_back(randNumber);
    }

    for (int i = 0; i < mineCount; i++) { //use those random numbers as indices and place a mine in that tile
        randNumber = randNumbers[i];
        tileGrid[randNumber].setMine(1);
    }
}

GameState::GameState(const char *filepath) {
    flagCount = 0;
    mineCount = 0;
    playStatus = PlayStatus::PLAYING;
    std::ifstream iStream;
    iStream.open(filepath);
    std::string readRow, currentRow;
    gameHeight = 0;
    tileGrid.clear();
    while (!iStream.eof()) {
        std::getline(iStream, readRow);
        if (readRow == "") //disregard if the line was just a newline character
            continue;
        currentRow = readRow;
        for (int col = 0; col < currentRow.length(); col++) { //iterate through each row
            Tile temp = Tile(sf::Vector2f(col * 32, gameHeight * 32));
            temp.setMine(((int) currentRow[col]) - 48); //converting characters 0 and 1 to int gives 48 and 49, so we subtract 48
            mineCount += ((int) currentRow[col]) - 48;
            tileGrid.push_back(temp);
        }
        gameHeight += 1;
    }
    gameWidth = currentRow.length();
}

Tile* GameState::getTile(int x, int y) {
    if (x >= gameWidth || y >= gameHeight)
        return nullptr;
    return &tileGrid[y * gameHeight + x];
}



