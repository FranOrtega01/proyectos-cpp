#include "HighscoreState.h"

void HighscoreState::init(){
    HighscoreFile hsFile;
    Highscore hs;
    _mainMenuBtn = new Button(_data,  250, 70, "MAIN MENU", 24, sf::Vector2f(SCREEN_WIDTH / 2 - 250 - 20,SCREEN_HEIGHT - 100));
    _exitBtn = new Button(_data,  250, 70, "EXIT", 24, sf::Vector2f(SCREEN_WIDTH / 2 + 20,SCREEN_HEIGHT - 100));

    if(hsFile.fileLength() > 0){
        stringstream ss;
        hs = hsFile.getHighscore();
        ss << "Highscore: " << hs.getScore() << "\n" << "\n" << "Player name: " << hs.getPlayerName();
        _text.setString(ss.str());

    }else{
        stringstream ss;
        ss << "NO HIGHSCORE SET, GO PLAY!";
        _text.setString(ss.str());
    }
    _text.setFont(_data->assets.getFont("Monocraft"));
    _text.setCharacterSize(32);
    _text.setPosition(sf::Vector2f(
        (SCREEN_WIDTH - _text.getGlobalBounds().width) / 2,
        200
    ));
    
}

HighscoreState::HighscoreState(GameDataRef data) : _data(data){
    init();
}

HighscoreState::~HighscoreState(){
    delete _mainMenuBtn;
    delete _exitBtn;
}

void HighscoreState::handleInput(){
    sf::Event ev;
    while(_data->window.pollEvent(ev)){
        if(sf::Event::Closed == ev.type) _data->window.close();
        // Buttons clicked
        if(_data->input.isSpriteClicked(_mainMenuBtn->getButton(), sf::Mouse::Left, _data->window)){
            _data->machine.addState(StateRef( new MainMenuState(_data)));
        }
        if(_data->input.isSpriteClicked(_exitBtn->getButton(), sf::Mouse::Left, _data->window)){
            _data->window.close();
        }
    }
}

void HighscoreState::update(float dt){
    _mainMenuBtn->update();
    _exitBtn->update();
}

void HighscoreState::draw(float dt){
    _data->window.clear(COLOR_BG_BLUE);

    _mainMenuBtn->draw();
    _exitBtn->draw();
    _data->window.draw(_text);

    _data->window.display();
}
