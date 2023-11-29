#ifndef ENDGAMESTATE_H
#define ENDGAMESTATE_H

#include "Game.h"
#include "Button.h"
#include "MainMenuState.h"

class GameOverState : public State{
    private:
        GameDataRef _data;
        sf::Text _title;
        Button *_mainMenuBtn;
        Button *_exitBtn;
        void init();
    public:
        GameOverState(GameDataRef data);
        ~GameOverState();
        void handleInput();
        void update( float dt );
        void draw( float dt );
};

#endif // ENDGAMESTATE_H
