#ifndef HIGHSCORESTATE_H
#define HIGHSCORESTATE_H

#include "State.h"
#include "Game.h"
#include "Button.h"
#include "MainMenuState.h"
#include "Highscore.h"

class HighscoreState:public State{
    private:
    GameDataRef _data;
    sf::Text _text;
    // sf::Text _hsPlayerName;

    Button *_mainMenuBtn;
    Button *_exitBtn;
    void init();
    public:
        HighscoreState(GameDataRef data);
        ~HighscoreState();

    void handleInput();
    void update(float dt);
    void draw(float dt);
};

#endif // HIGHSCORESTATE_H
