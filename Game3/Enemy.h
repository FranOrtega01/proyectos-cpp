#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "DEFINITIONS.h"
#include "Game.h"
#include "Functions.h"

class Enemy
{
    private:
        GameDataRef _data;
        sf::Sprite _sprite;
        int _animationIterator;
        bool _moving;
        sf::Clock _attackClock;
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
        float _health;
        float _maxHealth;
        sf::Vector2f _vel;
        sf::Vector2f _nextPos;

        sf::RectangleShape _healthBarBox;
        sf::RectangleShape _healthBarFill;

    public:
        Enemy(GameDataRef data, sf::Vector2f pos);

         // Getters
        sf::Sprite &getSprite(){return _sprite;}
        sf::Clock &getAttackClock(){return _attackClock;}
        float getDamage(){return _damage;}
        float getHealth(){return _health;}
        float getMaxHealth(){return _maxHealth;}
        bool getMoving(){return _moving;}
        sf::Vector2f getNextPos(){return _nextPos;}
        // Setters
        void setMoving(bool e){_moving = e;}
        void setVelocity(float x, float y){_vel = sf::Vector2f(x,y);}
        void setVelocity(sf::Vector2f vec){_vel = vec;}
        void setVelocityX(float x){_vel = sf::Vector2f(x, _vel.y);}
        void setVelocityY(float y){_vel = sf::Vector2f(_vel.x, y);}

        void moveEnemy(sf::Vector2f playerPos);
        void handleCollision(sf::FloatRect wallBounds);
        bool takeDamage(float dmg);
        void updateGUI();
        void animate();
        void update();
        void draw();
};

#endif // ENEMY_H
