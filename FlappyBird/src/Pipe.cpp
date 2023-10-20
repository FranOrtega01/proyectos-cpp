#include "Pipe.hpp"
#include "DEFINITIONS.hpp"

namespace Ramon{
    Pipe::Pipe(GameDataRef data) : _data(data){
        _landHeight = _data->assets.getTexture("Land").getSize().y;
        _pipeSpawnYOffset = 0;
    }

    void Pipe::spawnBottomPipes(){
        sf::Sprite sprite( _data->assets.getTexture("PipeUp"));
        sprite.setPosition(_data->window.getSize().x, _data->window.getSize().y - sprite.getGlobalBounds().height - _pipeSpawnYOffset);
        _pipeSprites.push_back(sprite);
    }

    void Pipe::spawnTopPipes(){
        sf::Sprite sprite( _data->assets.getTexture("PipeDown"));
        sprite.setPosition(_data->window.getSize().x, -_pipeSpawnYOffset);
        _pipeSprites.push_back(sprite);
    }

    void Pipe::spawnInvisiblePipe(){
        sf::Sprite sprite( _data->assets.getTexture("PipeUp"));
        sprite.setPosition(_data->window.getSize().x,  _data->window.getSize().y - sprite.getGlobalBounds().height);
        sprite.setColor(sf::Color(0,0,0,0));
        _pipeSprites.push_back(sprite);
    }

    void Pipe::spawnScoringPipe(){
        sf::Sprite sprite( _data->assets.getTexture("ScoringPipe"));
        sprite.setPosition(_data->window.getSize().x + sprite.getGlobalBounds().width,  0);
        sprite.setColor(sf::Color(0,0,0,0));
        _scoringSprites.push_back(sprite);

    }

    const std::vector<sf::Sprite> &Pipe::getSprites() const{
        return _pipeSprites;
    }

    std::vector<sf::Sprite> &Pipe::getScoringSprites(){
        return _scoringSprites;
    }

    void Pipe::movePipes(float dt){
        for(unsigned short int i = 0; i < _pipeSprites.size(); i++){
            if(_pipeSprites.at(i).getPosition().x + _pipeSprites.at(i).getGlobalBounds().width < 0){
                _pipeSprites.erase(_pipeSprites.begin() + i);
            }
            float movement = PIPE_SPEED * dt;
            _pipeSprites.at(i).move(-movement, 0);
        }

        for(unsigned short int i = 0; i < _scoringSprites.size(); i++){
            if(_scoringSprites.at(i).getPosition().x + _scoringSprites.at(i).getGlobalBounds().width < 0){
                _scoringSprites.erase(_scoringSprites.begin() + i);
            }else{
                float movement = PIPE_SPEED * dt;
                _scoringSprites.at(i).move(-movement, 0);
            }
        }
    }

    void Pipe::drawPipes()
    {
        for(unsigned short int i = 0; i < _pipeSprites.size(); i++){
            _data->window.draw(_pipeSprites.at(i));
        }
    }
    void Pipe::randomisePipeOffset(){
        _pipeSpawnYOffset = rand() % ( _landHeight + 1 );
    }
}