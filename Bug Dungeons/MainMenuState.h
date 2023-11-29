#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "Game.h"
#include "GameState.h"
#include "HighscoreState.h"
#include "Button.h"

class MainMenuState:public State{
    private:
        GameDataRef _data;
        sf::Text _title;
        Button* _playBtn;
        Button* _highscoreBtn;
        Button* _exitBtn;
        bool _mouseDown;
        void init();
    public:
        MainMenuState(GameDataRef data);

        void handleInput();
        void update( float dt );
        void draw( float dt );
};

#endif // MAINMENUSTATE_H
