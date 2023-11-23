#include "Player.h"
#include <iostream>

// Init
Player::Player(GameDataRef data) : _data(data){
    init();
}

void Player::init(){
    _moving = false;
    _colliding = false;
    _animationIterator = 0;
    _sprite.setTexture(_data->assets.getTexture("character"));
    _sprite.setTextureRect(_animations[_animationIterator]);
    _sprite.setScale(PLAYER_SCALE, PLAYER_SCALE);
    _sprite.setPosition(2 * TILE_SIZE * TILE_SCALE, 2 * TILE_SIZE * TILE_SCALE);

    _damage = PLAYER_BASE_DAMAGE;
    _speed = PLAYER_BASE_SPEED;
    _maxHealth = 50.0f;
    _health = _maxHealth;
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
            if(playerBounds.top < wallBounds.top &&
            playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height &&
            playerBounds.left < wallBounds.left + wallBounds.width &&
            playerBounds.left + playerBounds.width > wallBounds.left
            ){
                _sprite.setPosition(playerBounds.left, wallBounds.top - playerBounds.height - _speed);
            }
            // Top
            else if(playerBounds.top > wallBounds.top &&
            playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height &&
            playerBounds.left < wallBounds.left + wallBounds.width &&
            playerBounds.left + playerBounds.width > wallBounds.left
            ){
                _sprite.setPosition(playerBounds.left, wallBounds.top + wallBounds.height + _speed);
            }

            // Right
            if(playerBounds.left < wallBounds.left &&
            playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width &&
            playerBounds.top < wallBounds.top + wallBounds.height &&
            playerBounds.top + playerBounds.height > wallBounds.top
            ){
                _sprite.setPosition(wallBounds.left - playerBounds.width - _speed,playerBounds.top);
            }
            // Left
            else if(playerBounds.left > wallBounds.left &&
            playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width &&
            playerBounds.top < wallBounds.top + wallBounds.height &&
            playerBounds.top + playerBounds.height > wallBounds.top
            ){
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
        _speed += POTION_BASE_SPEED;
        break;
    case ePotions::damage:
        _damage += POTION_BASE_DAMAGE;
        break;
    default:
        break;
    }
}

void Player::animate(float dt){
    if(_moving && !_colliding){
        if(_clock.getElapsedTime().asSeconds() > PLAYER_ITERATION / 3){
        if(_animationIterator > 5) _animationIterator = 2;
        _sprite.setTextureRect(_animations[_animationIterator]);
        _animationIterator++;
        _clock.restart();
        }
    }else{
        if(_clock.getElapsedTime().asSeconds() > PLAYER_ITERATION){
            if(_animationIterator > 1) _animationIterator = 0;
            _sprite.setTextureRect(_animations[_animationIterator]);
            _animationIterator++;
            _clock.restart();
        }
    }
}

void Player::update(float dt){
    _moving = false;
    float x = 0.0f;
    float y = 0.0f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        y = -1.0f;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        y = 1.0f;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        x = -1.0f;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        x = 1.0f;
    }
    if(abs(x) + abs(y) != 0) handleMove(x, y);
}

void Player::draw(){
    _data->window.draw(_sprite);
}

