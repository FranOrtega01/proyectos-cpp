#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace Ramon{
    class MainMenuState:public State{
        private:
            GameDataRef _data;
            sf::Sprite _bg;
            sf::Sprite _title;
            sf::Sprite _playButton;
        public:
            MainMenuState(GameDataRef data);

            void init();
            void handleInput();
            void update( float dt );
            void draw( float dt );
    };
}