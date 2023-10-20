#include "Game.hpp"
#include "SplashState.hpp"

namespace Ramon{
    Game::Game(int width, int height, std::string title){
        _data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);


        // Add first state to machine
        _data->machine.addState(StateRef(new SplashState(this->_data)));
        run();
    }

    void Game::run(){
        float newTime, frameTime, interpolation;
        float currentTime = _clock.getElapsedTime().asSeconds();
        float acc = 0.0f;

        while(_data->window.isOpen()){
            _data->machine.processStateChanges();
            newTime = _clock.getElapsedTime().asSeconds();
            frameTime = newTime - currentTime;

            if(frameTime > 0.2f)frameTime = 0.25f;

            currentTime = newTime;
            acc += frameTime;

            while(acc >= dt){
                _data->machine.getActiveState()->handleInput();
                _data->machine.getActiveState()->update(dt);
                acc -= dt;
            }

            interpolation = acc / dt;
            _data->machine.getActiveState()->draw(interpolation);
        }
    }
}
