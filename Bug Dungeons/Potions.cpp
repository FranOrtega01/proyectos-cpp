#include "Potions.h"

Potions::Potions(GameDataRef data, int type, sf::Vector2f pos): _data(data){
    _type = type;

    switch (type)
    {
    case ePotions::heal:
        _sprite.setTexture(_data->assets.getTexture("PHealth"));
        break;
    case ePotions::speed:
        _sprite.setTexture(_data->assets.getTexture("PSpeed"));
        break;
    case ePotions::damage:
        _sprite.setTexture(_data->assets.getTexture("PDamage"));
        break;
    case ePotions::super:
        _sprite.setTexture(_data->assets.getTexture("SuperPotion"));
        break;
    default:
        break;
    }

    _sprite.setPosition(pos.x + _sprite.getGlobalBounds().width / 2, pos.y + _sprite.getGlobalBounds().height / 2);
    _sprite.scale(2,2);

}

void Potions::draw(){
    _data->window.draw(_sprite);
}
