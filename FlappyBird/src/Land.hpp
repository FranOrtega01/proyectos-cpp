#pragma once
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <vector>


namespace Ramon{
    class Land{
        private:
            GameDataRef _data;
            std::vector<sf::Sprite> _landSprites;
        public:
            Land(GameDataRef data);
            const std::vector<sf::Sprite> &getSprites() const;
            void moveLand(float dt);
            void drawLand();
    };
}