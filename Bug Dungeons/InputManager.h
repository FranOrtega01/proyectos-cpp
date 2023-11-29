#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SFML/Graphics.hpp>

class InputManager{
    private:
    public:
        bool isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window);
        bool isSpriteClicked(sf::RectangleShape object, sf::Mouse::Button button, sf::RenderWindow &window);
        sf::Vector2i getMousePos(sf::RenderWindow &window);
};
#endif // INPUTMANAGER_H
