#ifndef PROYECTILE_H
#define PROYECTILE_H

#include <SFML/Graphics.hpp>
#include "DEFINITIONS.h"
#include "Game.h"
#include "Functions.h"

class Proyectile
{
    private:
        GameDataRef _data;
        sf::CircleShape _sprite;
        sf::Vector2f _direction;
        float _damage;
        void init();
    public:
        Proyectile(GameDataRef data, float dmg, sf::Sprite playerSprite, sf::Vector2i direc, bool moving);
        // Getters
        sf::CircleShape &getSprite(){return _sprite;}
        float getDamage(){return _damage;}

        void update();
        void draw();
};

#endif // PROYECTILE_H
