#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "GameState.hpp"
#include "Highscore.hpp"

namespace Ramon{
    class GameOverState:public State{
        private:
            GameDataRef _data;
            sf::Sprite _bg;
            sf::Sprite _gameOverTitle;
            sf::Sprite _gameOverContainer;
            sf::Sprite _retryButton;
            
            sf::Sprite _medal;

            sf::Text _scoreText;
            sf::Text _highScoreText;

            int _score;
            int _highScore;
        public:
            GameOverState(GameDataRef data, int score);

            void init();
            void handleInput();
            void update( float dt );
            void draw( float dt );
    };
}