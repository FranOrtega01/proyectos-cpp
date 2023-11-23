#include "GameState.h"

GameState::GameState(GameDataRef data) : _data(data){
    initGUI();
}

GameState::~GameState(){
    delete _map;
    delete _player;
    delete _flash;
}

void GameState::init(){
    _data->assets.loadTexture("tilesheet", TILESHEET_PATH);
    _data->assets.loadTexture("character", CHARACTER_PATH);
    _data->assets.loadTexture("enemy", ENEMY_PATH);

    // _data->assets.loadFonts("Monocraft", FONT_PATH);
    if(!font.loadFromFile(FONT_PATH)){
        std::cout << "Error initializing font" << std::endl;
    }

    _map = new Map(_data);
    _walls = _map->getWalls();
    _player = new Player(_data);
    _flash = new Flash(_data);
    _spawners.push_back(Spawner(_data, sf::Vector2i(7, 3)));

    for(int i = 0; i < 5; i++){
        sf::Vector2f pos = randMapTile(_map->getMap()).sprite.getPosition();
        _potions.push_back(Potions(_data, randNumberBetween(3), pos));
    }

    _maxProys = 300;
    _mouseDown = false;
    _gameState = GameStates::ePlaying;
}

void GameState::initGUI(){
    _playerHealthBarBox = sf::RectangleShape(sf::Vector2f(GUI_HEALTH_LENGTH, GUI_HEALTH_HEIGHT));
    _playerHealthBarBox.setFillColor(sf::Color::Black);
    _playerHealthBarBox.setOutlineColor(sf::Color::Black);
    _playerHealthBarBox.setOutlineThickness(2.f);
    _playerHealthBarBox.setPosition(15.0f, 15.0f);

    _playerHealthBarFill = sf::RectangleShape(sf::Vector2f(GUI_HEALTH_LENGTH, GUI_HEALTH_HEIGHT));
    _playerHealthBarFill.setFillColor(sf::Color::Green);
    _playerHealthBarFill.setPosition(15.0f, 15.0f);

    _GUItext.setFont(font);
    _GUItext.setString("0");
    _GUItext.setCharacterSize(16);
    _GUItext.setFillColor(sf::Color::White);
    _GUItext.setPosition(5, 50);
}

void GameState::handleInput(){
    sf::Event ev;
    while(_data->window.pollEvent(ev)){
        if(sf::Event::Closed == ev.type) _data->window.close();
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(!_mouseDown){
                _mouseDown = true;
                spawnProy();
            }
        }else{
            _mouseDown = false;
        }
    }
}

void GameState::spawnProy(){
    if(_proys.size() < _maxProys){
        _proys.push_back(Proyectile(_data, _player->getDamage(), _player->getSprite(), _data->input.getMousePos(_data->window), _player->getMoving()));
    }
}

void GameState::checkHit(int spawner, int enemy){
    for(unsigned int i = 0; i< _proys.size(); i++){
        if(_spawners[spawner].checkHit(_proys[i].getSprite().getGlobalBounds(),enemy, _proys[i].getDamage())){
            _proys.erase(_proys.begin() + i);
        }
    }
}

void GameState::spawnerHit(int s){
    for(unsigned int i = 0; i< _proys.size(); i++){
        if(_spawners[s].getEnemyQty() == 0 && _proys[i].getSprite().getGlobalBounds().intersects(_spawners[s].getSprite().getGlobalBounds())){
            if(!_spawners[s].takeDamage(_player->getDamage())){
                _spawners.erase(_spawners.begin() + i);
            }
            _proys.erase(_proys.begin() + i);
        }
    }
}

void GameState::updateEnemy(){
    for(unsigned int i = 0; i < _spawners.size(); i++){
        int enemies = _spawners[i].getEnemyQty();
        spawnerHit(i);
        for(int e = 0; e < enemies; e++){
            Enemy& enemy = _spawners[i].getEnemy(e);
            enemy.moveEnemy(_player->getSprite().getPosition());
            checkHit(i, e);
            if(enemy.getSprite().getGlobalBounds().intersects(_player->getSprite().getGlobalBounds()) && enemy.getAttackClock().getElapsedTime().asSeconds() > ENEMY_ATTACK_SPEED){
                if(!_player->takeDamage(enemy.getDamage())) endGame();
                updateGUI();
                enemy.getAttackClock().restart();
            }
        }
    }
}
void GameState::updatePlayer(float dt){
    _player->animate(dt);
    for(unsigned int i = 0; i < _potions.size(); i++){
        if(spriteCollision(_player->getSprite(), _potions[i].getSprite())){
            _player->pickPotion(_potions[i]);
            _potions.erase(_potions.begin() + i);
        }
    }
    _player->update(dt);
}


void GameState::handleCollision(){
    for(int i = 0; i < _walls.size(); i++){
        sf::FloatRect wallBounds = _walls[i].sprite.getGlobalBounds();

        _player->handleCollision(wallBounds);

        for(unsigned int i = 0; i < _proys.size(); i++){
            if(wallBounds.intersects(_proys[i].getSprite().getGlobalBounds())) _proys.erase(_proys.begin() + i);
        }
        for(unsigned int i = 0; i < _spawners.size(); i++){
            _spawners[i].handleEnemyCollision(wallBounds);
        }
    }
}

void GameState::updateGUI(){
    float percent = _player->getHealth() / _player->getMaxHealth();
    _playerHealthBarFill.setSize(sf::Vector2f(GUI_HEALTH_LENGTH * percent, GUI_HEALTH_HEIGHT));
    _playerHealthBarFill.setFillColor(generateHealthColor(percent));

    std::stringstream ss;
    ss << "Speed: " << _player->getSpeed() << "\n" << "Damage: " << _player->getDamage();
    _GUItext.setString(ss.str());
}

void GameState::update(float dt){
    if(_gameState == GameStates::ePlaying){
        _map->update(dt);

        for(unsigned int i = 0; i < _spawners.size(); i++){
            _spawners[i].handleSpawn();
        }

        for(unsigned int i = 0; i < _proys.size(); i++){
            _proys[i].update();
        }

        updateEnemy();
        updatePlayer(dt);
        handleCollision();
        updateGUI();
    }

    if(_gameState == GameStates::eGameOver){
        for(unsigned int i = 0; i < _spawners.size(); i++){
            _spawners[i].despawnAll();
        }
        _flash->show(dt);
        if(_endGameClock.getElapsedTime().asSeconds() > TIME_BEFORE_GAME_OVER){
            // _data->machine.addState(StateRef( new GameOverState(_data, _score)));
        }
    }
}

void GameState::drawGUI(){
    _data->window.draw(_playerHealthBarBox);
    _data->window.draw(_playerHealthBarFill);
    _data->window.draw(_GUItext);
}

void GameState::draw(float dt){
    _data->window.clear();
    _map->draw();

    for(unsigned int i = 0; i < _spawners.size(); i++){
        _spawners[i].draw();
    }

    for(unsigned int i = 0; i < _proys.size(); i++){
        _proys[i].draw();
    }

    for(unsigned int i = 0; i < _potions.size(); i++){
        _potions[i].draw();
    }

    _player->draw();
    drawGUI();
    _flash->draw();
    _data->window.display();
}

void GameState::endGame(){
    _gameState = GameStates::eGameOver;
    _endGameClock.restart();
}
