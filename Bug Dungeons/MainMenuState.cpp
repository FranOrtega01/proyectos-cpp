#include "MainMenuState.h"

void MainMenuState::init(){
    _data->assets.loadFonts("Monocraft", FONT_PATH);
    _title.setFont(_data->assets.getFont("Monocraft"));
    _title.setString("Main Menu");
    _title.setCharacterSize(32);
    _title.setPosition(sf::Vector2f((SCREEN_WIDTH - _title.getGlobalBounds().width) / 2, 100));

    _playBtn = new Button(_data,  250, 80, "PLAY", 24);

    sf::Vector2f highscoreBtnPos = sf::Vector2f(( SCREEN_WIDTH - _playBtn->getButton().getGlobalBounds().width) / 2 , _playBtn->getButton().getGlobalBounds().top + _playBtn->getButton().getGlobalBounds().height + 25);
    _highscoreBtn = new Button(_data,  250, 80, "HIGHSCORE", 24, highscoreBtnPos);

    sf::Vector2f _exitBtnPos = sf::Vector2f(( SCREEN_WIDTH - _highscoreBtn->getButton().getGlobalBounds().width) / 2 , _highscoreBtn->getButton().getGlobalBounds().top + _highscoreBtn->getButton().getGlobalBounds().height + 25);
    _exitBtn = new Button(_data,  250, 80, "EXIT", 24, _exitBtnPos);
}

MainMenuState::MainMenuState(GameDataRef data) : _data(data){ init(); }

void MainMenuState::handleInput(){
    sf::Event ev;
    while(_data->window.pollEvent(ev)){
        if(sf::Event::Closed == ev.type) _data->window.close();
        if(_data->input.isSpriteClicked(_playBtn->getButton(), sf::Mouse::Left, _data->window)){
            _data->machine.addState(StateRef( new GameState(_data)));
        }
        if(_data->input.isSpriteClicked(_highscoreBtn->getButton(), sf::Mouse::Left, _data->window)){
            _data->machine.addState(StateRef( new HighscoreState(_data)));
        }
        if(_data->input.isSpriteClicked(_exitBtn->getButton(), sf::Mouse::Left, _data->window)){
            _data->window.close();
        }
    }
}

void MainMenuState::update(float dt){
    _playBtn->update();
    _highscoreBtn->update();
    _exitBtn->update();
}

void MainMenuState::draw(float dt){
    sf::RectangleShape bg = sf::RectangleShape(_data->window.getView().getSize());
    bg.setPosition(
        _data->window.getView().getCenter().x - bg.getGlobalBounds().width / 2,
        _data->window.getView().getCenter().y - bg.getGlobalBounds().height / 2
    );
    bg.setFillColor(COLOR_BG_BLUE);

    _data->window.clear();
    _data->window.draw(bg);
    _data->window.draw(_title);
    _playBtn->draw();
    _highscoreBtn->draw();
    _exitBtn->draw();
    _data->window.display();
}
