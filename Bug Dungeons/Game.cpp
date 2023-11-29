#include "Game.h"
#include "MainMenuState.h"

Game::Game(int width, int height, std::string title)
{
    // Init window
    sf::Image icon;
    icon.loadFromFile("assets/icon.jpg");
    _data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);

    _data->window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Add first state to machine (Main Menu)
    _data->machine.addState(StateRef(new MainMenuState(this->_data)));
    run();
}

void Game::run(){
    float newTime, frameTime, interpolation;
    float currentTime = _clock.getElapsedTime().asSeconds();
    float acc = 0.0f;

    while(_data->window.isOpen()){
        newTime = _clock.getElapsedTime().asSeconds();
        frameTime = newTime - currentTime;

        if(frameTime > 0.2f)frameTime = 0.25f;

        currentTime = newTime;
        acc += frameTime;

        if(acc >= dt){
            _data->machine.getActiveState()->handleInput();
            _data->machine.getActiveState()->update(dt);
            _data->machine.getActiveState()->draw(dt);
            acc -= dt;
        }
    }
}
