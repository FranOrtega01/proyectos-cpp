#pragma once
#include <SFML/Graphics.hpp>

namespace Ramon{
    class InputManager{
        private:
        public:
            InputManager(){}
            ~InputManager(){}
            bool isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window);
            sf::Vector2i getMousePos(sf::RenderWindow &window);
    };
}