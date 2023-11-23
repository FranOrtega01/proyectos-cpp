#ifndef FLASH_H
#define FLASH_H

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "DEFINITIONS.h"

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
