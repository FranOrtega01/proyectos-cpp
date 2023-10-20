#pragma once
#include "SFML/Graphics.hpp"
#include "DEFINITIONS.hpp"
#include "Game.hpp"

namespace Ramon{
    class HUD{
        private:
            GameDataRef _data;
            sf::Text _scoreText;
        public:
            HUD(GameDataRef data);
            void draw();
            void updateScore(int score);
    };

}