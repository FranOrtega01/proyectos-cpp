#include <sstream>
#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

namespace Ramon{
    MainMenuState::MainMenuState(GameDataRef data) : _data(data){

	}

    void MainMenuState::init(){
        _data->assets.loadTexture("MainMenuBg", MAIN_MENU_BG_FILEPATH);
        _data->assets.loadTexture("GameTitle", GAME_TITLE_FILEPATH);
        _data->assets.loadTexture("PlayButton", PLAY_BUTTON_FILEPATH);

        _bg.setTexture(_data->assets.getTexture("MainMenuBg"));
        _title.setTexture(_data->assets.getTexture("GameTitle"));
        _playButton.setTexture(_data->assets.getTexture("PlayButton"));

        _title.setPosition(( SCREEN_WIDTH - _title.getGlobalBounds().width) / 2 , _title.getGlobalBounds().height / 2 );

        _playButton.setPosition(( SCREEN_WIDTH - _playButton.getGlobalBounds().width) / 2 , (SCREEN_HEIGHT - _playButton.getGlobalBounds().height) / 2 );

    }

    void MainMenuState::handleInput(){
        sf::Event ev;
        while(_data->window.pollEvent(ev)){
            if(sf::Event::Closed == ev.type) _data->window.close();
            if(_data->input.isSpriteClicked(_playButton, sf::Mouse::Left, _data->window)){
                _data->machine.addState(StateRef( new GameState(_data)));
            }
        }
    }

    void MainMenuState::update(float dt){   

    }

    void MainMenuState::draw(float dt){
        _data->window.clear();
        _data->window.draw(_bg);
        _data->window.draw(_title);
        _data->window.draw(_playButton);
        _data->window.display();
    }
}