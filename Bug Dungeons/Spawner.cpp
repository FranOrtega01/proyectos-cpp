#include "Spawner.h"
#include <iostream>
Spawner::Spawner(GameDataRef data, sf::Vector2i pos) : _data(data){
    _sprite.setTexture(_data->assets.getTexture("tilesheet"));
    _sprite.setTextureRect(sf::IntRect(9 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
    _sprite.setScale(TILE_SCALE, TILE_SCALE);
    _sprite.setPosition(pos.x * TILE_SCALE * TILE_SIZE, pos.y * TILE_SCALE * TILE_SIZE);

    _maxEnemies = 4;
    _maxHealth = 15.0f;
    _health = _maxHealth;

    int randEnemies = _maxEnemies - randNumberBetween(_maxEnemies-1);

    for(int i = 0; i < randEnemies; i++){
        _enemies.push_back(Enemy(
            _data,
            randomCoord(
                sf::Vector2f(
                    _sprite.getPosition().x + _sprite.getGlobalBounds().width / 2,
                    _sprite.getPosition().y + _sprite.getGlobalBounds().height / 2),
                TILE_SCALE * TILE_SIZE))
        );
    }
}

bool Spawner::takeDamage(float dmg){
    _health = _health - dmg <= 0 ? 0 : _health - dmg;
    return _health;
}

bool Spawner::checkHit(sf::FloatRect proyBounds,int e, float dmg){
    if(proyBounds.intersects(_enemies[e].getSprite().getGlobalBounds())){
        if(!_enemies[e].takeDamage(dmg)){
            _enemies.erase(_enemies.begin() + e);
        }
        return true;
    }
    return false;
}

void Spawner::handleEnemyCollision(sf::FloatRect wallBounds){
    for(unsigned int i = 0; i < _enemies.size(); i++){
        _enemies[i].handleCollision(wallBounds);
    }
}

void Spawner::despawnAll(){
    _enemies.clear();
}

void Spawner::handleSpawn(){
    if(_spawnClock.getElapsedTime().asSeconds() > ENEMY_SPAWN_TIME){
        int enemies = _enemies.size();

        for(int i = 0; i < _maxEnemies - enemies; i++){
            _enemies.push_back(Enemy(
                _data,
                randomCoord(
                    sf::Vector2f(
                        _sprite.getPosition().x + _sprite.getGlobalBounds().width / 2,
                        _sprite.getPosition().y + _sprite.getGlobalBounds().height / 2),
                    TILE_SCALE * TILE_SIZE))
            );
        }
        _spawnClock.restart();
    }
}

void Spawner::eraseEnemy(int i){
    _enemies.erase(_enemies.begin() + i);
}

void Spawner::draw(){
    _data->window.draw(_sprite);
    for(unsigned int i = 0; i < _enemies.size(); i++){
        _enemies[i].draw();
    }
}
