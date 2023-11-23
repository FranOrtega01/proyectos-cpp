#include "Enemy.h"
#include <iostream>
Enemy::Enemy(GameDataRef data, sf::Vector2f pos) : _data(data){
    _moving = false;
    _animationIterator = 3;
    _sprite.setTexture(_data->assets.getTexture("enemy"));
    _sprite.setTextureRect(_animations[_animationIterator]);
    _sprite.setScale(PLAYER_SCALE, PLAYER_SCALE);
    _sprite.setPosition(pos.x - _sprite.getGlobalBounds().width / 2, pos.y - _sprite.getGlobalBounds().height / 2);

    _damage = 10.0f;
    _maxHealth = 10.0f;
    _health = _maxHealth;

    _healthBarBox = sf::RectangleShape(sf::Vector2f(_sprite.getGlobalBounds().width, 4.0f));
    _healthBarBox.setFillColor(sf::Color::Transparent);
    _healthBarBox.setOutlineColor(sf::Color::Black);
    _healthBarBox.setOutlineThickness(1.f);
    _healthBarBox.setPosition(_sprite.getPosition().x + 1.f, _sprite.getPosition().y + 3.f);

    _healthBarFill = sf::RectangleShape(sf::Vector2f(_sprite.getGlobalBounds().width, 4.0f));
    _healthBarFill.setFillColor(sf::Color(224, 9, 9));
    _healthBarFill.setPosition(_sprite.getPosition().x + 1.f, _sprite.getPosition().y + 3.f);
}


void Enemy::moveEnemy(sf::Vector2f playerPos){
    sf::Vector2f direction = playerPos - _sprite.getPosition();
    float normal = distance(playerPos, _sprite.getPosition());
    normal == 0 ? setVelocity(0, 0) : setVelocity(direction/normal);
    if(normal < 200) _sprite.move(_vel.x * ENEMY_SPEED, _vel.y * ENEMY_SPEED);

    _healthBarBox.setPosition(_sprite.getPosition().x + 1.f, _sprite.getPosition().y + 6.f);
    _healthBarFill.setPosition(_sprite.getPosition().x + 1.f, _sprite.getPosition().y + 6.f);

    _nextPos.x = _sprite.getGlobalBounds().left + ENEMY_SPEED * _vel.x;
    _nextPos.y = _sprite.getGlobalBounds().top + ENEMY_SPEED * _vel.y;
}

void Enemy::handleCollision(sf::FloatRect wallBounds){
    sf::FloatRect enemyBounds = _sprite.getGlobalBounds();
    sf::FloatRect nextPosBounds = enemyBounds;
    nextPosBounds.left = _nextPos.x;
    nextPosBounds.top = _nextPos.y;

    if(wallBounds.intersects(nextPosBounds)){
            // Bottom Collision
            if(enemyBounds.top < wallBounds.top &&
            enemyBounds.top + enemyBounds.height < wallBounds.top + wallBounds.height &&
            enemyBounds.left < wallBounds.left + wallBounds.width &&
            enemyBounds.left + enemyBounds.width > wallBounds.left
            ){
                _sprite.setPosition(enemyBounds.left, wallBounds.top - enemyBounds.height - ENEMY_SPEED);
            }
            // Top
            else if(enemyBounds.top > wallBounds.top &&
            enemyBounds.top + enemyBounds.height > wallBounds.top + wallBounds.height &&
            enemyBounds.left < wallBounds.left + wallBounds.width &&
            enemyBounds.left + enemyBounds.width > wallBounds.left
            ){
                _sprite.setPosition(enemyBounds.left, wallBounds.top + wallBounds.height + ENEMY_SPEED);
            }

            // Right
            if(enemyBounds.left < wallBounds.left &&
            enemyBounds.left + enemyBounds.width < wallBounds.left + wallBounds.width &&
            enemyBounds.top < wallBounds.top + wallBounds.height &&
            enemyBounds.top + enemyBounds.height > wallBounds.top
            ){
                _sprite.setPosition(wallBounds.left - enemyBounds.width - ENEMY_SPEED,enemyBounds.top);
            }
            // Left
            else if(enemyBounds.left > wallBounds.left &&
            enemyBounds.left + enemyBounds.width > wallBounds.left + wallBounds.width &&
            enemyBounds.top < wallBounds.top + wallBounds.height &&
            enemyBounds.top + enemyBounds.height > wallBounds.top
            ){
                _sprite.setPosition(wallBounds.left + wallBounds.width + ENEMY_SPEED,enemyBounds.top);

            }
        }
}

bool Enemy::takeDamage(float dmg){
    _health = _health - dmg <= 0 ? 0 : _health - dmg;
    updateGUI();
    return _health;
}

void Enemy::animate(){

}

void Enemy::updateGUI(){
    float percent = _health / _maxHealth;
    _healthBarFill.setSize(sf::Vector2f(_sprite.getGlobalBounds().width * percent, 4.0f));
}

void Enemy::draw(){
    _data->window.draw(_sprite);
    _data->window.draw(_healthBarBox);
    _data->window.draw(_healthBarFill);
}
