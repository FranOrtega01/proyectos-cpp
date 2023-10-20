#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace Ramon{
    class SplashState:public State{
        private:
            GameDataRef _data;
            sf::Clock _clock;
            sf::Sprite _bg;
        public:
            SplashState(GameDataRef data);

            void init();
            void handleInput();
            void update( float dt );
            void draw( float dt );
    };
}