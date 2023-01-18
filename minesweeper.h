#pragma once



int launch();
void restart();
void render();
void toggleDebugMode();
bool getDebugMode();
void gameLoop();
void testBoard1();
void testBoard2();

Toolbox* toolbox = Toolbox::getInstance();
GameState gameState;
