#ifndef BUTTON_H
#define BUTTON_H

#include "Game.h"
#include "Functions.h"

class Button{
    private:
        GameDataRef _data;
        float _width;
        float _height;
        sf::Text _text;
        sf::RectangleShape _box;
        void initBox(sf::Vector2f pos);
        void initText(std::string text, int fontSize);
    public:
        Button(GameDataRef data, float width, float height, std::string text,int fontSize, sf::Vector2f pos = sf::Vector2f(-1, -1));
        Button(GameDataRef data, sf::Vector2f size, std::string text,int fontSize, sf::Vector2f pos = sf::Vector2f(-1, -1));

        sf::RectangleShape &getButton(){return _box;}

        void update();
        void draw();
};

#endif // BUTTON_H
