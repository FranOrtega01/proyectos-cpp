#include "Land.hpp"
#include "DEFINITIONS.hpp"

namespace Ramon{
    Land::Land(GameDataRef data) : _data(data){
        sf::Sprite sprite( _data->assets.getTexture("Land"));
        sf::Sprite sprite2( _data->assets.getTexture("Land"));

        sprite.setPosition(0, _data->window.getSize().y - sprite.getGlobalBounds().height);
        sprite2.setPosition(sprite.getGlobalBounds().width, _data->window.getSize().y - sprite.getGlobalBounds().height);

        _landSprites.push_back(sprite);
        _landSprites.push_back(sprite2);
    }

    const std::vector<sf::Sprite> &Land::getSprites() const{
        return _landSprites;
    }

    void Land::moveLand(float dt){
        for(unsigned short int i = 0; i < _landSprites.size();i++){
            if(_landSprites.at(i).getPosition().x + _landSprites.at(i).getGlobalBounds().width < 0){
                sf::Vector2f pos(_data->window.getSize().x, _landSprites.at(i).getPosition().y);
                _landSprites.at(i).setPosition(pos);
            }else{
                float movement = PIPE_SPEED * dt;
                _landSprites.at(i).move(-movement, 0);
            }
        }
    }

    void Land::drawLand(){
        for(unsigned short int i = 0; i < _landSprites.size(); i++){
            _data->window.draw(_landSprites.at(i));
        }
    }
}