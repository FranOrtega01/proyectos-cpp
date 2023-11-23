#include "MainMenuState.h"

#include <iostream>

MainMenuState::MainMenuState(GameDataRef data) : _data(data){}

void MainMenuState::init(){
    _data->assets.loadTexture("MainMenuBg", MAIN_MENU_BG_PATH);
    _bg.setTexture(_data->assets.getTexture("MainMenuBg"));
    // _title.setPosition(( SCREEN_WIDTH - _title.getGlobalBounds().width) / 2 , _title.getGlobalBounds().height / 2 );
    _playButton = sf::RectangleShape(sf::Vector2f(300.0f, 100.0f));
    _playButton.setFillColor(sf::Color::Green);
    _playButton.setPosition(( SCREEN_WIDTH - _playButton.getGlobalBounds().width) / 2 , (SCREEN_HEIGHT - _playButton.getGlobalBounds().height) / 2 );

    _exitButton = sf::RectangleShape(sf::Vector2f(300.0f, 100.0f));
    _exitButton.setFillColor(sf::Color::Red);
    _exitButton.setPosition(( SCREEN_WIDTH - _playButton.getGlobalBounds().width) / 2 , _playButton.getGlobalBounds().top + _playButton.getGlobalBounds().height + 50);
}

void MainMenuState::handleInput(){
    sf::Event ev;
    while(_data->window.pollEvent(ev)){
        if(sf::Event::Closed == ev.type) _data->window.close();
        if(_data->input.isSpriteClicked(_playButton, sf::Mouse::Left, _data->window)){
            _data->machine.addState(StateRef( new GameState(_data)));
        }
        if(_data->input.isSpriteClicked(_exitButton, sf::Mouse::Left, _data->window)){
            _data->window.close();
        }
    }
}

void MainMenuState::update(float dt){

}

void MainMenuState::draw(float dt){
    _data->window.clear();
    _data->window.draw(_bg);
    // _data->window.draw(_title);
    _data->window.draw(_playButton);
    _data->window.draw(_exitButton);
    _data->window.display();
}
