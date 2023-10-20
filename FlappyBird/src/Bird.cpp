#include "Bird.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

namespace Ramon{
    Bird::Bird(GameDataRef data) : _data(data) {
        _animationIterator = 0;
        _animationFrames.push_back(_data->assets.getTexture("BirdFrame1")); 
        _animationFrames.push_back(_data->assets.getTexture("BirdFrame2")); 
        _animationFrames.push_back(_data->assets.getTexture("BirdFrame3")); 
        _animationFrames.push_back(_data->assets.getTexture("BirdFrame4")); 

        _birdSprite.setTexture(_animationFrames.at(_animationIterator));
        _birdSprite.setPosition( (_data->window.getSize().x / 4 - _birdSprite.getGlobalBounds().width / 2), (_data->window.getSize().y - _birdSprite.getGlobalBounds(). height) / 2);
        _birdState = BIRD_STATE_STILL;

        sf::Vector2f origin = sf::Vector2f(_birdSprite.getGlobalBounds().width / 2 , _birdSprite.getGlobalBounds().height / 2);
        _birdSprite.setOrigin(origin);
        _rotation = 0;
        _birdSpeed = FLYING_SPEED;
        _birdGravity = GRAVITY;
    }

    const sf::Sprite &Bird::getSprite() const{
        return _birdSprite;
    }

    void Bird::animate(float dt){

        if(_clock.getElapsedTime().asSeconds() > BIRD_ANIMATION_DURATION / _animationFrames.size() ){
            if( _animationIterator == _animationFrames.size() - 1){
                _animationIterator = 0;
            }else{
                _animationIterator++;
            }
            _birdSprite.setTexture(_animationFrames.at(_animationIterator));
            _clock.restart();
        }
    }

    void Bird::update(float dt){
        if(_birdState == BIRD_STATE_FALLING){
            // std::cout<< _birdGravity << std::endl;
            _birdGravity += 5.0f * dt / dt;
            _birdSprite.move(0, _birdGravity * dt);
            _rotation += ROTATATION_SPEED * dt;
            if(_rotation > 25.0f) _rotation = 25.0f;

            _birdSprite.setRotation(_rotation);
        }else if(_birdState == BIRD_STATE_FLYING){
            // std::cout << _birdSpeed << std::endl;
            // _birdSpeed = _birdSpeed - (FLYING_SPEED / FLYING_DURATION) * dt;

            float tiempo_transcurrido = _movementClock.getElapsedTime().asSeconds();
            std::cout << tiempo_transcurrido << std::endl;
            float birdAcceleration = FLYING_SPEED / (FLYING_DURATION * FLYING_DURATION);
            _birdSpeed = FLYING_SPEED - (birdAcceleration * tiempo_transcurrido * tiempo_transcurrido);

            _birdSprite.move(0, -_birdSpeed * dt );
            _rotation -= ROTATATION_SPEED * 2.0f * dt;
            if(_rotation < -25.0f) _rotation = -25.0f;

            _birdSprite.setRotation(_rotation);
            
        }

        if(_movementClock.getElapsedTime().asSeconds() > FLYING_DURATION){
            _movementClock.restart();
            _birdState = BIRD_STATE_FALLING;
        }
    }

    void Bird::tap(){
        _movementClock.restart();
        _birdSpeed = FLYING_SPEED;
        _birdState = BIRD_STATE_FLYING;
        _birdGravity = 100;
    }

    void Bird::draw(){
        _data->window.draw(_birdSprite);
    }
}