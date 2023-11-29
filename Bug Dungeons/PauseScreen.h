#ifndef PAUSESCREEN_H
#define PAUSESCREEN_H

#include "Game.h"
#include "Button.h"

class PauseScreen
{
    private:
        GameDataRef _data;
        sf::Text _text;
        Button *_saveBtn;
        Button *_exitBtn;

    public:
        PauseScreen(GameDataRef data);
        ~PauseScreen();

        sf::RectangleShape &getSaveButton(){
            return _saveBtn->getButton();
        }
        sf::RectangleShape &getExitButton(){
            return _exitBtn->getButton();
        }
        
        void update();
        void draw();
};

#endif // PAUSESCREEN_H


