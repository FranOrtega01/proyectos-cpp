#ifndef WINSTATE_H
#define WINSTATE_H

#include "Game.h"
#include "Button.h"
#include "MainMenuState.h"
#include "Highscore.h"

class WinState:public State{
    private:
        GameDataRef _data;
        int _score, _fileHighscore;
        bool _isHighscore;
        sf::Text _title;
        sf::Text _scoreText;
        sf::Text _playerNameText;
        sf::Text _playerName;
        Button* _mainMenuBtn;
        Button* _exitBtn;
        Button* _hsBtn;

        void init();
        void initTexts();
    public:
        WinState(GameDataRef data, int score);
        ~WinState();
        void handleInput();
        void update(float dt);
        void draw(float dt);
};

#endif // WINSTATE_H
