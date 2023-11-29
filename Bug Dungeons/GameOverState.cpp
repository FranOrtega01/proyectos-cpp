#include "GameOverState.h"

void GameOverState::init(){
    _title.setFont(_data->assets.getFont("Monocraft"));
    _title.setString("You died!");
    _title.setCharacterSize(32);
    _title.setPosition(sf::Vector2f((SCREEN_WIDTH - _title.getGlobalBounds().width) / 2 - 8, 100));

    _mainMenuBtn = new Button(_data, 250, 80, "MAIN MENU", 24);

    sf::Vector2f _exitButtonPos = sf::Vector2f(( SCREEN_WIDTH - _mainMenuBtn->getButton().getGlobalBounds().width) / 2 , _mainMenuBtn->getButton().getGlobalBounds().top + _mainMenuBtn->getButton().getGlobalBounds().height + 50);
    _exitBtn = new Button(_data, 250, 80, "EXIT", 24, _exitButtonPos);
}

GameOverState::GameOverState(GameDataRef data) : _data(data) {
    init();
}

GameOverState::~GameOverState(){
    delete _mainMenuBtn;
    delete _exitBtn;
}


void GameOverState::handleInput(){
    sf::Event ev;
    while(_data->window.pollEvent(ev)){
        if(sf::Event::Closed == ev.type) _data->window.close();
        if(_data->input.isSpriteClicked(_mainMenuBtn->getButton(), sf::Mouse::Left, _data->window)){
            _data->machine.addState(StateRef(new MainMenuState(_data)));
        }
        if(_data->input.isSpriteClicked(_exitBtn->getButton(), sf::Mouse::Left, _data->window)){
            _data->window.close();
        }
    }
}

void GameOverState::update(float dt){
    _mainMenuBtn->update();
    _exitBtn->update();
}

void GameOverState::draw(float dt){
    sf::RectangleShape bg = sf::RectangleShape(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    bg.setFillColor(sf::Color(19, 23, 36));

    _data->window.clear();
    _data->window.draw(bg);
    _data->window.draw(_title);
    _mainMenuBtn->draw();
    _exitBtn->draw();

    _data->window.display();
}
