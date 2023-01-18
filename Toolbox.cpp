#include "Toolbox.h"

Toolbox* Toolbox::instance = nullptr;

Toolbox::Toolbox() {}

Toolbox* Toolbox::getInstance() {
    if (instance == nullptr)
        instance = new Toolbox();
    return instance;
}

Toolbox::~Toolbox() {
    delete instance;
    delete newGameButton;
    delete debugButton;
    delete testButton1;
    delete testButton2;
}

