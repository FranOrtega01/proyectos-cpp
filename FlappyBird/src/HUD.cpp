#include "HUD.hpp"

namespace Ramon{
    HUD::HUD(GameDataRef data) : _data(data){
        _scoreText.setFont(_data->assets.getFont("FlappyFont"));
        _scoreText.setString("0");
        _scoreText.setCharacterSize(128);
        _scoreText.setFillColor(sf::Color::White);
        _scoreText.setOrigin(_scoreText.getGlobalBounds().width / 2, _scoreText.getGlobalBounds().height / 2 );
        _scoreText.setPosition(_data->window.getSize().x / 2, _data->window.getSize().y / 5);
    }

    void HUD::updateScore(int score){
        _scoreText.setString(std::to_string(score));
    }

    void HUD::draw(){
        _data->window.draw(_scoreText);
    }
}