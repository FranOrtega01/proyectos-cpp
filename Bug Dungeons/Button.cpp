#include "Button.h"

void Button::initBox(sf::Vector2f pos){
    _box = sf::RectangleShape(sf::Vector2f(_width, _height));
    _box.setFillColor(sf::Color::Transparent);
    _box.setOutlineThickness(4);
    _box.setOutlineColor(sf::Color::White);

    if(pos == sf::Vector2f(-1, -1)){
        _box.setPosition(sf::Vector2f(
            (SCREEN_WIDTH - _box.getGlobalBounds().width) / 2,
            (SCREEN_HEIGHT - _box.getGlobalBounds().height) / 2));
    }else{
        _box.setPosition(pos);
    }
}

void Button::initText(std::string text, int fontSize){
    _text.setFont(_data->assets.getFont("Monocraft"));
    _text.setCharacterSize(fontSize);
    _text.setFillColor(sf::Color::White);
    _text.setString(text);
    _text.setPosition(sf::Vector2f(
        (_box.getPosition().x + _box.getSize().x / 2 - _text.getGlobalBounds().width / 2) - 2,
        (_box.getPosition().y + _box.getSize().y / 2 - _text.getGlobalBounds().height / 2) - 2
    ));
}

Button::Button(GameDataRef data, float width, float height, std::string text, int fontSize ,sf::Vector2f pos) : _data(data){
    _width = width;
    _height = height;

    initBox(pos);
    initText(text, fontSize);
}

Button::Button(GameDataRef data, sf::Vector2f size, std::string text, int fontSize, sf::Vector2f pos) : _data(data) {
    _width = size.x;
    _height = size.y;
    initBox(pos);
    initText(text, fontSize);
}

void Button::update(){
    if(isMouseInside(_box, _data->window)){
        _box.setOutlineColor( COLOR_YELLOW );
        _text.setColor( COLOR_YELLOW );
    }else{
        _box.setOutlineColor(sf::Color::White);
        _text.setColor(sf::Color::White);
    }
}

void Button::draw(){
    _data->window.draw(_box);
    _data->window.draw(_text);
}
