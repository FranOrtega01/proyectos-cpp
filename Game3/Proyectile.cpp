#include "Proyectile.h"
#include "iostream"
Proyectile::Proyectile(GameDataRef data, float dmg, sf::Sprite playerSprite,sf::Vector2i mousePos, bool moving) : _data(data){
    sf::Vector2f playerCenter = sf::Vector2f(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2 - _sprite.getGlobalBounds().width / 2 , playerSprite.getPosition().y + playerSprite.getGlobalBounds().height / 2 - _sprite.getGlobalBounds().height / 2);
    _sprite.setRadius(3);
    _sprite.setFillColor(sf::Color::White);
    _sprite.setPosition(playerCenter);

    _damage = dmg;

    sf::Vector2f newMousePos = sf::Vector2f(mousePos);
    if(moving){
        newMousePos.x += (rand() % PLAYER_RECOIL) - (PLAYER_RECOIL / 2);
        newMousePos.y += (rand() % PLAYER_RECOIL) - (PLAYER_RECOIL / 2);
    }

    float normal = distance(playerCenter, sf::Vector2f(newMousePos));
    sf::Vector2f direc = sf::Vector2f(newMousePos) - playerCenter;

    _direction = sf::Vector2f(direc.x / normal, direc.y / normal);
}

void Proyectile::update(){
    _sprite.move(_direction * PROY_SPEED);
}

void Proyectile::draw(){
    _data->window.draw(_sprite);
}
