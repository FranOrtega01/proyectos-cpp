#include "InputManager.hpp"

namespace Ramon{
    bool InputManager::isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window){
        if(sf::Mouse::isButtonPressed(button)){
        sf::IntRect tempRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getLocalBounds().height);
            if(tempRect.contains(sf::Mouse::getPosition(window))){
                return true;
            }
        }
        return false;
    }

    sf::Vector2i InputManager::getMousePos(sf::RenderWindow &window){
        return sf::Mouse::getPosition(window);
    }
}
