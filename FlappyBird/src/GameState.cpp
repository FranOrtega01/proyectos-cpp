#include "GameState.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

namespace Ramon{
    GameState::GameState(GameDataRef data) : _data(data){}

    void GameState::init(){ 
        _data->assets.loadTexture("GameStateBg", GAME_BG_FILEPATH);
        _data->assets.loadTexture("PipeUp", PIPE_UP_FILEPATH);
        _data->assets.loadTexture("PipeDown", PIPE_DOWN_FILEPATH);
        _data->assets.loadTexture("ScoringPipe", SCORING_PIPE_FILEPATH);
        _data->assets.loadTexture("Land", LAND_FILEPATH);
        _data->assets.loadTexture("BirdFrame1", BIRD_FRAME_1_FILEPATH);
        _data->assets.loadTexture("BirdFrame2", BIRD_FRAME_2_FILEPATH);
        _data->assets.loadTexture("BirdFrame3", BIRD_FRAME_3_FILEPATH);
        _data->assets.loadTexture("BirdFrame4", BIRD_FRAME_4_FILEPATH);

        _data->assets.loadFonts("FlappyFont", FLAPPY_FONT_FILEPATH);

        pipe = new Pipe(_data);
        land = new Land(_data);
        bird = new Bird(_data);
        flash = new Flash(_data);
        hud = new HUD(_data);

        _bg.setTexture(_data->assets.getTexture("GameStateBg"));
        _score = 0;
        hud->updateScore(_score);

        mouseDown = false;

        _gameState = GameStates::eReady;
    }

    void GameState::handleInput(){
        sf::Event ev;
        while(_data->window.pollEvent(ev)){
            if(sf::Event::Closed == ev.type) _data->window.close();

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                if(!this->mouseDown){
                    this->mouseDown = true;
                    if(_data->input.isSpriteClicked(_bg, sf::Mouse::Left, _data->window)){
                        if(_gameState != GameStates::eGameOver){
                            _gameState = GameStates::ePlaying;
                            bird->tap();
                        }
                    }
                }
            }else{
                this->mouseDown = false;
            } 
        }
    }

    void GameState::checkCollisions(){
        std::vector<sf::Sprite> landSprites = land->getSprites();
        std::vector<sf::Sprite> pipeSprites = pipe->getSprites();

        if(bird->getSprite().getPosition().y <= 0){
            _gameState = GameStates::eGameOver;
            _clock.restart();
        }

        for(int i = 0; i < landSprites.size(); i++){
            if(Collision.checkSpriteCollision(bird->getSprite(), 0.7f, landSprites.at(i), 1.0f)){
                _gameState = GameStates::eGameOver;
                _clock.restart();
            }
        }

        for(int i = 0; i < pipeSprites.size(); i++){
            if(Collision.checkSpriteCollision(bird->getSprite(),0.625f, pipeSprites.at(i), 1.0f)){
                _gameState = GameStates::eGameOver;
                _clock.restart();
            }
        }
        if(_gameState == GameStates::ePlaying){
            std::vector<sf::Sprite> &scoringSprites = pipe->getScoringSprites();
            for(int i = 0; i < scoringSprites.size(); i++){
                if(Collision.checkSpriteCollision(bird->getSprite(), 0.625f, scoringSprites.at(i), 1.0f)){
                    _score++;
                    hud->updateScore(_score);
                    scoringSprites.erase(scoringSprites.begin() + i);
                }
            }
        }
    }

    void GameState::update(float dt){
        if(_gameState != GameStates::eGameOver){
            bird->animate(dt);
            land->moveLand(dt);
        }
        if(_gameState == GameStates::ePlaying){
            if(_clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQ ){
                pipe->randomisePipeOffset();
                // pipe->spawnInvisiblePipe();
                pipe->spawnBottomPipes();
                pipe->spawnTopPipes();
                pipe->spawnScoringPipe();

                _clock.restart();
            }
            pipe->movePipes(dt);
            bird->update(dt);

            checkCollisions();
        }
        if(_gameState == GameStates::eGameOver){
            flash->show(dt);
            if(_clock.getElapsedTime().asSeconds() > TIME_BEFORE_GAME_OVER_APPEAR){
                _data->machine.addState(StateRef( new GameOverState(_data, _score)));
            }
        }
    }

    void GameState::draw(float dt){
        _data->window.clear();
        _data->window.draw(_bg);
        pipe->drawPipes();
        land->drawLand();
        bird->draw();
        flash->draw();
        hud->draw();
        _data->window.display();
    }
}