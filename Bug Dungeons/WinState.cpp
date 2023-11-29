#include "WinState.h"
using namespace std;

void WinState::init(){
    _mainMenuBtn = new Button(_data,  250, 70, "MAIN MENU", 24, sf::Vector2f(SCREEN_WIDTH / 2 - 250 - 20,SCREEN_HEIGHT - 100));
    _exitBtn = new Button(_data,  250, 70, "EXIT", 24, sf::Vector2f(SCREEN_WIDTH / 2 + 20,SCREEN_HEIGHT - 100));
    if(_isHighscore){
        _hsBtn = new Button(_data,250,70, "SET HIGHSCORE",24, sf::Vector2f(SCREEN_WIDTH / 2 - 125, SCREEN_HEIGHT - 200));
    }
}

void WinState::initTexts(){
    _title.setFont(_data->assets.getFont("Monocraft"));
    _title.setString("You Win!");
    _title.setCharacterSize(48);
    _title.setFillColor(COLOR_YELLOW);
    _title.setPosition(sf::Vector2f((SCREEN_WIDTH - _title.getGlobalBounds().width) / 2, 50));

    std::stringstream ss;
    ss << "Score: " << _score << " Highscore: " << _fileHighscore;
    _scoreText.setFont(_data->assets.getFont("Monocraft"));
    _scoreText.setString(ss.str());
    _scoreText.setCharacterSize(28);
    _scoreText.setPosition(sf::Vector2f(
        (SCREEN_WIDTH - _scoreText.getGlobalBounds().width) / 2,
        _title.getGlobalBounds().top + _title.getGlobalBounds().height + 50
    ));


    if(_isHighscore){
        ss.str("");
        ss << "It's a highscore! Enter your name: ";
        _playerNameText.setFont(_data->assets.getFont("Monocraft"));
        _playerNameText.setCharacterSize(24);
        _playerNameText.setString(ss.str());
        _playerNameText.setPosition(sf::Vector2f(
            (SCREEN_WIDTH - _playerNameText.getGlobalBounds().width) / 2,
            _scoreText.getGlobalBounds().top + _scoreText.getGlobalBounds().height + 50
        ));

        _playerName.setFont(_data->assets.getFont("Monocraft"));
        _playerName.setCharacterSize(32);
        _playerName.setString("");
        _playerName.setPosition(sf::Vector2f(
            (SCREEN_WIDTH - _playerName.getGlobalBounds().width) / 2,
            _playerNameText.getGlobalBounds().top + _playerNameText.getGlobalBounds().height + 40
        ));
    }

}

WinState::WinState(GameDataRef data, int score) : _data(data), _score(score){
    _isHighscore = false;
    HighscoreFile hsFile;
    Highscore hs;
    _fileHighscore = hsFile.getHighscore().getScore();
    if(_fileHighscore < score || hsFile.fileLength() <= 0){
        _isHighscore = true;
    }
    init();
    initTexts();
}

WinState::~WinState(){
    _mainMenuBtn;
    _exitBtn;
    _hsBtn;
}

void WinState::handleInput(){
    sf::Event ev;
    while(_data->window.pollEvent(ev)){
        if(sf::Event::Closed == ev.type) _data->window.close();
        // User Text
        if (ev.type == sf::Event::TextEntered && _isHighscore) {
            // Check if its printable char
            if (ev.text.unicode < 128 && ev.text.unicode != 8 && _playerName.getString().getSize() < 3) {
                // a-zA-Z0-9
                if ((ev.text.unicode >= 'A' && ev.text.unicode <= 'Z') || (ev.text.unicode >= 'a' && ev.text.unicode <= 'z') || (ev.text.unicode >= '0' && ev.text.unicode <= '9')) {
                    char newChar = static_cast<char>(std::toupper(ev.text.unicode));
                    _playerName.setString(_playerName.getString() + newChar);
                }
            } else if (ev.text.unicode == 8 && _playerName.getString().getSize() > 0) {
                std::string currentText = _playerName.getString();
                currentText.pop_back();
                _playerName.setString(currentText);
            }
            _playerName.setPosition((SCREEN_WIDTH - _playerName.getGlobalBounds().width) / 2, _playerName.getPosition().y);
        }
        // Buttons clicked
        if(_data->input.isSpriteClicked(_mainMenuBtn->getButton(), sf::Mouse::Left, _data->window)){
            _data->machine.addState(StateRef( new MainMenuState(_data)));
        }
        if(_data->input.isSpriteClicked(_exitBtn->getButton(), sf::Mouse::Left, _data->window)){
            _data->window.close();
        }
        if(_isHighscore && _playerName.getString().getSize() > 0 && _data->input.isSpriteClicked(_hsBtn->getButton(), sf::Mouse::Left, _data->window)){
            HighscoreFile hsFile;
            Highscore hs;
            sf::String sfmlString = _playerName.getString();
            char playerNameChar[4];
            stringToChar(playerNameChar, _playerName.getString());

            hs.setHighscore(_score, playerNameChar);
            hsFile.setHighscore(hs);
            _data->machine.addState(StateRef( new MainMenuState(_data)));
        }
    }
}

void WinState::update(float dt){
    _mainMenuBtn->update();
    _exitBtn->update();
    if(_isHighscore){
        _hsBtn->update();
    }
}

void WinState::draw(float dt){
    sf::RectangleShape bg = sf::RectangleShape(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    bg.setFillColor(sf::Color(19, 23, 36));

    _data->window.clear();
    _data->window.draw(bg);
    _data->window.draw(_title);
    _data->window.draw(_scoreText);
    _mainMenuBtn->draw();
    _exitBtn->draw();
    if(_isHighscore){
        _hsBtn->draw();
        _data->window.draw(_playerNameText);
        _data->window.draw(_playerName);

        if(_playerName.getString().getSize() == 0){
            sf::Text warning;
            warning.setFont(_data->assets.getFont("Monocraft"));
            warning.setCharacterSize(12);
            warning.setString("Name must have at least 1 char");
            warning.setPosition(sf::Vector2f(
            (SCREEN_WIDTH - warning.getGlobalBounds().width) / 2,
            _playerNameText.getGlobalBounds().top + _playerNameText.getGlobalBounds().height + 5
        ));
            warning.setFillColor(sf::Color::Red);
            _data->window.draw(warning);
        }
    }
    _data->window.display();
}
