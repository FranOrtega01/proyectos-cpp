#ifndef FLASH_H
#define FLASH_H

#include "Game.h"

class Flash
{
private:
    GameDataRef _data;
    sf::RectangleShape _shape;
    bool _flashOn;

public:
    Flash(GameDataRef data);
    void show(float dt);
    void draw();
};

#endif // FLASH_H
