#ifndef SPAWNER_H
#define SPAWNER_H

#include <SFML/Graphics.hpp>
#include "DEFINITIONS.h"
#include "Game.h"
#include "Functions.h"
#include "Enemy.h"

class Spawner
{
    private:
        GameDataRef _data;
        std::vector<Enemy> _enemies;
        sf::Sprite _sprite;
        sf::Clock _spawnClock;
        int _maxEnemies;

        float _maxHealth, _health;
    public:
        Spawner(GameDataRef data, sf::Vector2i pos);
        // Getters
        sf::Sprite &getSprite(){return _sprite;}
        Enemy &getEnemy(int idx){return _enemies[idx];}
        int getEnemyQty(){return _enemies.size();}

        void handleSpawn();
        void eraseEnemy(int i);
        bool takeDamage(float dmg);
        bool checkHit(sf::FloatRect proyBounds,int enemy, float dmg);
        void handleEnemyCollision(sf::FloatRect wallBounds);
        void despawnAll();
        void update();
        void draw();
};

#endif // SPAWNER_H
