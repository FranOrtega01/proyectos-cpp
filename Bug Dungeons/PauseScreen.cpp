#include "PauseScreen.h"

PauseScreen::PauseScreen(GameDataRef data) : _data(data){
    _text.setFont(_data->assets.getFont("Monocraft"));
    _text.setString("Game paused");
    _text.setCharacterSize(32);
    _text.setPosition(
        _data->window.getView().getCenter().x - _text.getGlobalBounds().width / 2,
        100
    );

    _saveBtn = new Button(_data,  250, 80, "SAVE", 24);

    sf::Vector2f _exitButtonPos = sf::Vector2f(( SCREEN_WIDTH - _saveBtn->getButton().getGlobalBounds().width) / 2 , _saveBtn->getButton().getGlobalBounds().top + _saveBtn->getButton().getGlobalBounds().height + 50);
    _exitBtn = new Button(_data,  250, 80, "EXIT", 24, _exitButtonPos);
}

PauseScreen::~PauseScreen(){
    delete _saveBtn;
    delete _exitBtn;
}

void PauseScreen::update(){
    _saveBtn->update();
    _exitBtn->update();
}

void PauseScreen::draw()
{
    sf::RectangleShape filter = sf::RectangleShape(_data->window.getView().getSize());
    filter.setPosition(
        _data->window.getView().getCenter().x - filter.getGlobalBounds().width / 2,
        _data->window.getView().getCenter().y - filter.getGlobalBounds().height / 2
    );
    filter.setFillColor(sf::Color(19, 23, 36, 40));
    _data->window.draw(filter);
    _data->window.draw(_text);
    _saveBtn->draw();
    _exitBtn->draw();
}
