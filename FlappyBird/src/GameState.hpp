#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "GameOverState.hpp"
#include "Pipe.hpp"
#include "Land.hpp"
#include "Bird.hpp"
#include "Collision.hpp"
#include "Flash.hpp"
#include "HUD.hpp"

namespace Ramon{
    class GameState:public State{
        private:
            GameDataRef _data;
            sf::Sprite _bg;
            Pipe *pipe;
            Land *land;
            Bird *bird;
            Collision Collision;
            Flash *flash;
            HUD *hud;
            sf::Clock _clock;
            int _gameState;

            bool mouseDown;
            int _score;

        public:
            GameState(GameDataRef data);

            void init();
            void handleInput();
            void checkCollisions();
            void update( float dt );
            void draw( float dt );
    };
}