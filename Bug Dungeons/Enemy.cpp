#include "Enemy.h"
#include <iostream>

void Enemy::initHealthBar(){
    _healthBarBox = sf::RectangleShape(sf::Vector2f(_sprite.getGlobalBounds().width, ENEMY_HEALTH_BAR_HEIGTH));
    _healthBarBox.setFillColor(sf::Color::Transparent);
    _healthBarBox.setOutlineColor(sf::Color::Black);
    _healthBarBox.setOutlineThickness(1.f);
    _healthBarBox.setPosition(_sprite.getPosition().x + 1.f, _sprite.getPosition().y + 3.f);

    _healthBarFill = sf::RectangleShape(sf::Vector2f(_sprite.getGlobalBounds().width, ENEMY_HEALTH_BAR_HEIGTH));
    _healthBarFill.setFillColor(sf::Color(224, 9, 9));
    _healthBarFill.setPosition(_sprite.getPosition().x + 1.f, _sprite.getPosition().y + 3.f);
}
Enemy::Enemy(GameDataRef data, sf::Vector2f pos) : _data(data)
{
    _moving = false;
    _animationIterator = 0;
    _sprite.setTexture(_data->assets.getTexture("enemy"));
    _sprite.setTextureRect(_animations[_animationIterator]);
    _sprite.setScale(PLAYER_SCALE, PLAYER_SCALE);
    _sprite.setPosition(pos.x - _sprite.getGlobalBounds().width / 2, pos.y - _sprite.getGlobalBounds().height / 2);

    _damage = ENEMY_BASE_DAMAGE;
    _maxHealth = ENEMY_MAX_HEALTH;
    _health = _maxHealth;

    initHealthBar();
}

void Enemy::moveEnemy(sf::Vector2f playerPos){
    sf::Vector2f direction = playerPos - _sprite.getPosition();
    float normal = distance(playerPos, _sprite.getPosition());
    normal == 0 ? setVelocity(0, 0) : setVelocity(direction/normal);
    if(normal < ENEMY_DISTANCE) _sprite.move(_vel.x * ENEMY_SPEED, _vel.y * ENEMY_SPEED);

    _healthBarBox.setPosition(_sprite.getPosition().x + 1.f, _sprite.getPosition().y + 3.f);
    _healthBarFill.setPosition(_sprite.getPosition().x + 1.f, _sprite.getPosition().y + 3.f);

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
            if(spriteBoundsBottomCollision(enemyBounds, wallBounds)){
                _sprite.setPosition(enemyBounds.left, wallBounds.top - enemyBounds.height - ENEMY_SPEED);
            }
            // Top
            else if(spriteBoundsTopCollision(enemyBounds, wallBounds)){
                _sprite.setPosition(enemyBounds.left, wallBounds.top + wallBounds.height + ENEMY_SPEED);
            }

            // Right
            if(spriteBoundsRightCollision(enemyBounds, wallBounds)){
                _sprite.setPosition(wallBounds.left - enemyBounds.width - ENEMY_SPEED,enemyBounds.top);
            }
            // Left
            else if(spriteBoundsLeftCollision(enemyBounds, wallBounds)){
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
    if(_animationClock.getElapsedTime().asSeconds() > PLAYER_ITERATION / 2){
        if(_animationIterator > 1) _animationIterator = 0;
        _sprite.setTextureRect(_animations[_animationIterator]);
        _animationIterator++;
        _animationClock.restart();
    }
}

void Enemy::updateGUI(){
    float percent = _health / _maxHealth;
    _healthBarFill.setSize(sf::Vector2f(_sprite.getGlobalBounds().width * percent, ENEMY_HEALTH_BAR_HEIGTH));
}

void Enemy::draw(){
    _data->window.draw(_sprite);
    _data->window.draw(_healthBarBox);
    _data->window.draw(_healthBarFill);
}
