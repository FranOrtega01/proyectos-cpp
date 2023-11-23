#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"
#include "GameState.h"
#include "DEFINITIONS.h"

class MainMenuState:public State{
    private:
        GameDataRef _data;
        // sf::Sprite _bg;
        // sf::Sprite _playButton;
        sf::Sprite _bg;
        sf::RectangleShape _playButton;
        sf::RectangleShape _exitButton;
    public:
        MainMenuState(GameDataRef data);

        void init();
        void handleInput();
        void update( float dt );
        void draw( float dt );
};

#endif // MAINMENUSTATE_H
