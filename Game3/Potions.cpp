#include "Potions.h"

Potions::Potions(GameDataRef data, int type, sf::Vector2f pos): _data(data){
    _type = type;
    _sprite = sf::RectangleShape(sf::Vector2f(40, 40));
    _sprite.setPosition(pos);

    switch (type)
    {
    case ePotions::heal:
        _sprite.setFillColor(sf::Color::Green);
        break;
    case ePotions::speed:
        _sprite.setFillColor(sf::Color::Cyan);
        break;
    case ePotions::damage:
        _sprite.setFillColor(sf::Color::Magenta);
        break;
    default:
        break;
    }
}

void Potions::draw(){
    _data->window.draw(_sprite);
}
