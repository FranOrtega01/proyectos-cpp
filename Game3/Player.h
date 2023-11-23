#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "DEFINITIONS.h"
#include "Game.h"
#include "Map.h"
#include "Tile.h"
#include "Potions.h"
#include "cmath"

class Player
{
    private:
        GameDataRef _data;
        sf::Sprite _sprite;
        sf::Clock _clock;
        bool _moving;
        bool _colliding;
        int _animationIterator;
        sf::IntRect _animations[10] = {
            sf::IntRect(0 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE),
            sf::IntRect(1 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE),
            sf::IntRect(0 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE),
            sf::IntRect(1 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE),
            sf::IntRect(2 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE),
            sf::IntRect(3 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE),
            sf::IntRect(4 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE),
        };
        float _damage;
        float _speed;
        float _health;
        float _maxHealth;
        sf::Vector2f _vel;
        sf::Vector2f _nextPos;

        void init();
    public:
        Player(GameDataRef data);

        // Getters
        sf::Sprite &getSprite(){return _sprite;}
        float getDamage(){return _damage;}
        float getSpeed(){return _speed;}
        float getHealth(){return _health;}
        float getMaxHealth(){return _maxHealth;}
        bool getMoving(){return _moving;}
        sf::Vector2f getNextPos(){return _nextPos;}
//        int* getCurrentTile();
//        int* getNextPosCurrentTile();

        // Setters
        void setMoving(bool e = true){_moving = e;}
        void setColliding(bool e = true){_colliding = e;}
        void setVelocity(float x, float y){_vel = sf::Vector2f(x,y);}
        void setVelocity(sf::Vector2f vec){_vel = vec;}
        void setVelocityX(float x){_vel = sf::Vector2f(x, _vel.y);}
        void setVelocityY(float y){_vel = sf::Vector2f(_vel.x, y);}

        void handleMove(float xDirection, float yDirection);
        void handleCollision(sf::FloatRect wallBounds);
        bool takeDamage(float dmg);
        void pickPotion(Potions potion);
        void animate(float dt);
        void update(float dt);
        void draw();
};

#endif // PLAYER_H
