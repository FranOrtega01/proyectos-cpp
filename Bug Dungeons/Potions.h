#ifndef POTIONS_H
#define POTIONS_H

#include "Map.h"
#include "Tile.h"
#include "Game.h"
#include "DEFINITIONS.h"

class Potions{
    private:
        GameDataRef _data;
        int _type;
        sf::Sprite _sprite;
    public:
        Potions(GameDataRef data, int type, sf::Vector2f pos);
        sf::Sprite &getSprite(){return _sprite;}
        int getTipe(){return _type;}
        void draw();
};

#endif // POTIONS_H
