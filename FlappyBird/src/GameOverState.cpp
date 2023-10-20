#include <sstream>
#include "GameOverState.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

namespace Ramon{
    GameOverState::GameOverState(GameDataRef data, int score) : _data(data), _score(score){
        HighscoreFile hsFile;
        Highscore hs;

        if(hsFile.getHighscore().getHighscore() < score || hsFile.fileLength() <= 0){
            _highScore = score;
            hs.setHighscore(score);
            hsFile.setHighscore(hs);
        }else{
            _highScore = hsFile.getHighscore().getHighscore();
        }
	}

    void GameOverState::init(){ 
        _data->assets.loadTexture("GameOverStateBg", GAME_OVER_BG_FILEPATH);
        _data->assets.loadTexture("GameOverStateTitle", GAME_OVER_TITLE_FILEPATH);
        _data->assets.loadTexture("GameOverStateBody", GAME_OVER_BODY_FILEPATH);
        _data->assets.loadTexture("BronzeMedal", BRONZE_MEDAL_FILEPATH);
        _data->assets.loadTexture("SilverMedal", SILVER_MEDAL_FILEPATH);
        _data->assets.loadTexture("GoldMedal", GOLD_MEDAL_FILEPATH);
        _data->assets.loadTexture("PlatinumMedal", PLATINUM_MEDAL_FILEPATH);

        _bg.setTexture(_data->assets.getTexture("GameOverStateBg"));
        _gameOverTitle.setTexture(_data->assets.getTexture("GameOverStateTitle"));
        _gameOverContainer.setTexture(_data->assets.getTexture("GameOverStateBody"));
        _retryButton.setTexture(_data->assets.getTexture("PlayButton"));

        _gameOverContainer.setPosition((_data->window.getSize().x - _gameOverContainer.getGlobalBounds().width) / 2, (_data->window.getSize().y - _gameOverContainer.getGlobalBounds().height) / 2 );

        _gameOverTitle.setPosition((_data->window.getSize().x - _gameOverTitle.getGlobalBounds().width) / 2, _gameOverContainer.getPosition().y - _gameOverTitle.getGlobalBounds().height * 1.2);

        _retryButton.setPosition((_data->window.getSize().x - _retryButton.getGlobalBounds().width) / 2, _gameOverContainer.getPosition().y + _gameOverContainer.getGlobalBounds().height + _retryButton.getGlobalBounds().height * 0.2);

        _scoreText.setFont(_data->assets.getFont("FlappyFont"));
        _scoreText.setString(std::to_string(_score));
        _scoreText.setCharacterSize(56);
        _scoreText.setFillColor(sf::Color::White);
        _scoreText.setOrigin(_scoreText.getGlobalBounds().width / 2, _scoreText.getGlobalBounds().height / 2);
        _scoreText.setPosition(_data->window.getSize().x / 10 * 7.25, _data->window.getSize().y / 2.15);

        _highScoreText.setFont(_data->assets.getFont("FlappyFont"));
        _highScoreText.setString(std::to_string(_highScore));
        _highScoreText.setCharacterSize(56);
        _highScoreText.setFillColor(sf::Color::White);
        _highScoreText.setOrigin(_highScoreText.getGlobalBounds().width / 2, _highScoreText.getGlobalBounds().height / 2);
        _highScoreText.setPosition(_data->window.getSize().x / 10 * 7.25, _data->window.getSize().y / 1.78);

        if(_score >= PLATINUM_MEDAL_SCORE){
            _medal.setTexture(_data->assets.getTexture("PlatinumMedal"));
        }else if(_score >= GOLD_MEDAL_SCORE){
            _medal.setTexture(_data->assets.getTexture("GoldMedal"));
        }else if(_score >= SILVER_MEDAL_SCORE){
            _medal.setTexture(_data->assets.getTexture("SilverMedal"));
        }else{
            _medal.setTexture(_data->assets.getTexture("BronzeMedal"));
        }

        _medal.setPosition(175, 465);
    }

    void GameOverState::handleInput(){
        sf::Event ev;
        while(_data->window.pollEvent(ev)){
            if(sf::Event::Closed == ev.type) _data->window.close();
            if(_data->input.isSpriteClicked(_retryButton, sf::Mouse::Left, _data->window)){
                _data->machine.addState(StateRef( new GameState(_data)));
            }
        }
    }

    void GameOverState::update(float dt){

    }

    void GameOverState::draw(float dt){
        _data->window.clear();
        _data->window.draw(_bg);
        _data->window.draw(_gameOverContainer);
        _data->window.draw(_gameOverTitle);
        _data->window.draw(_retryButton);
        _data->window.draw(_scoreText);
        _data->window.draw(_highScoreText);
        _data->window.draw(_medal);
        _data->window.display();
    }
}