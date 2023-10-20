#include <sstream>
#include "SplashState.hpp"
#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

namespace Ramon{
    SplashState::SplashState(GameDataRef data) : _data(data){

	}

    void SplashState::init(){
        _data->assets.loadTexture("SplashStateBg", SPLASH_SCENE_BG_FLIEPATH);
        _bg.setTexture(_data->assets.getTexture("SplashStateBg"));
    }

    void SplashState::handleInput(){
        sf::Event ev;
        while(_data->window.pollEvent(ev)){
            if(sf::Event::Closed == ev.type) _data->window.close();
        }
    }

    void SplashState::update(float dt){
        if(_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOWTIME){
            _data->machine.addState(StateRef( new MainMenuState(_data)));
        }
    }

    void SplashState::draw(float dt){
        _data->window.clear();
        _data->window.draw(_bg);
        _data->window.display();
    }
}