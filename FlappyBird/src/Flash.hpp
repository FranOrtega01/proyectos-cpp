#pragma once
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "DEFINITIONS.hpp"

namespace Ramon{
    class Flash{
        private:
            GameDataRef _data;
            sf::RectangleShape _shape;
            bool _flashOn;


        public:
            Flash(GameDataRef data);
            void show(float dt);
            void draw();

    };
}