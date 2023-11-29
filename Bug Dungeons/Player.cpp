#include "Player.h"
#include <iostream>

// Init
Player::Player(GameDataRef data) : _data(data){
    init();
}

void Player::init(){
    _moving = false;
    _reloading = false;
    _hasDamageEffect = false;
    _hasSpeedEffect = false;
    _hasSuperPotionEffect = false;
    _animationIterator = 0;
    _sprite.setTexture(_data->assets.getTexture("character"));
    _sprite.setTextureRect(_standingAnimatios[_animationIterator]);
    _sprite.setScale(PLAYER_SCALE, PLAYER_SCALE);
    _sprite.setPosition(2 * TILE_SIZE * TILE_SCALE + TILE_SIZE * TILE_SCALE / 2, 2 * TILE_SIZE * TILE_SCALE + TILE_SIZE * TILE_SCALE / 2);

    _damage = PLAYER_BASE_DAMAGE;
    _speed = PLAYER_BASE_SPEED;
    _maxHealth = PLAYER_MAX_HEALTH;
    _health = _maxHealth;
    _maxAmmo = PLAYER_AMMO;
    _ammo = _maxAmmo;
    _vel = sf::Vector2f(0, 0);
    _nextPos = sf::Vector2f(_sprite.getGlobalBounds().left, _sprite.getGlobalBounds().top);
}
// Functions
void Player::handleMove(float xDirection, float yDirection){

    // Vector
    float normal = sqrt(xDirection * xDirection + yDirection*yDirection);
    normal == 0 ? setVelocity(0, 0) : setVelocity(xDirection / normal, yDirection / normal);

    _sprite.move( _speed * _vel.x, _speed * _vel.y);
    _moving = true;
    _nextPos.x = _sprite.getGlobalBounds().left + _speed * _vel.x;
    _nextPos.y = _sprite.getGlobalBounds().top + _speed * _vel.y;
}

void Player::handleCollision(sf::FloatRect wallBounds){
    sf::FloatRect playerBounds = _sprite.getGlobalBounds();
    sf::Vector2f nextPos = _nextPos;
    sf::FloatRect nextPosBounds = playerBounds;
    nextPosBounds.left = nextPos.x;
    nextPosBounds.top = nextPos.y;

    if(wallBounds.intersects(nextPosBounds)){
        // Bottom Collision
        if(spriteBoundsBottomCollision(playerBounds, wallBounds)){
            _sprite.setPosition(playerBounds.left, wallBounds.top - playerBounds.height - _speed);
        }
        // Top
        else if(spriteBoundsTopCollision(playerBounds, wallBounds)){
            _sprite.setPosition(playerBounds.left, wallBounds.top + wallBounds.height + _speed);
        }
        // Right
        if(spriteBoundsRightCollision(playerBounds, wallBounds)){
            _sprite.setPosition(wallBounds.left - playerBounds.width - _speed,playerBounds.top);
        }
        // Left
        else if(spriteBoundsLeftCollision(playerBounds, wallBounds)){
            _sprite.setPosition(wallBounds.left + wallBounds.width + _speed,playerBounds.top);
        }
    }
}

bool Player::takeDamage(float dmg){
    if(_health - dmg <= 0){
        _health = 0;
        _sprite.setTextureRect(sf::IntRect(4 * TILE_SIZE, 4 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
    }else _health = _health - dmg;
    return _health;
}

void Player::pickPotion(Potions potion){
    switch (potion.getTipe())
    {
    case ePotions::heal:
        _health = _health + POTION_BASE_HEAL > _maxHealth ? _maxHealth : _health + POTION_BASE_HEAL;
        break;
    case ePotions::speed:
        _speed = PLAYER_BASE_SPEED + POTION_BASE_SPEED;
        _hasSpeedEffect = true;
        _speedPotionClock.restart();
        break;
    case ePotions::damage:
        _damage = PLAYER_BASE_DAMAGE + POTION_BASE_DAMAGE;
        _hasDamageEffect = true;
        _damagePotionClock.restart();
        break;
    case ePotions::super:
        _hasSuperPotionEffect = true;
        _superPotionClock.restart();
        break;
    default:
        break;
    }
}

void Player::clearPotionEffect(){
    if(_hasSpeedEffect && _speedPotionClock.getElapsedTime().asSeconds() > POTION_DURATION){
        _speed = PLAYER_BASE_SPEED;
        _hasSpeedEffect = false;
    }
    if(_hasDamageEffect && _damagePotionClock.getElapsedTime().asSeconds() > POTION_DURATION){
        _damage = PLAYER_BASE_DAMAGE;
        _hasDamageEffect = false;
    }
    if(_hasSuperPotionEffect && _superPotionClock.getElapsedTime().asSeconds() > POTION_DURATION) _hasSuperPotionEffect = false;
}

void Player::handleReload(){
    if (_reloading){
        if (_reloadClock.getElapsedTime().asSeconds() > PLAYER_RELOAD_TIME) {
            _ammo = _maxAmmo;
            _reloading = false;
        }
    }
}

bool Player::handleShoot(){
    if(_ammo > 0){
        if(!_hasSuperPotionEffect) _ammo--;
        return true;
    }
    return false;
}

void Player::animate(float dt){
    if(_moving){
        if(_animationClock.getElapsedTime().asSeconds() > PLAYER_ITERATION / 6){
            if(_animationIterator > 3) _animationIterator = 0;
            _sprite.setTextureRect(_movingAnimations[_animationIterator]);
            _animationIterator++;
            _animationClock.restart();
        }
    }else{
        if(_animationClock.getElapsedTime().asSeconds() > PLAYER_ITERATION / 2){
            if(_animationIterator > 1) _animationIterator = 0;
            _sprite.setTextureRect(_standingAnimatios[_animationIterator]);
            _animationIterator++;
            _animationClock.restart();
        }
    }
}

void Player::update(float dt){
    _moving = false;
    float x = 0.0f;
    float y = 0.0f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        y += -1.0f;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        y += 1.0f;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        x += -1.0f;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        x += 1.0f;
    }
    if(abs(x) + abs(y) != 0) handleMove(x, y);

    animate(dt);
    handleReload();
    clearPotionEffect();
}

void Player::draw(){
    _data->window.draw(_sprite);
}
