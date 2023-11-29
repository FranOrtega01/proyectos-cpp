#include "GameState.h"

void GameState::init(){
    // Textures
    _data->assets.loadTexture("tilesheet", TILESHEET_PATH);
    _data->assets.loadTexture("character", CHARACTER_PATH);
    _data->assets.loadTexture("enemy", ENEMY_PATH);
    _data->assets.loadTexture("PHealth", POTION_HEALTH_PATH);
    _data->assets.loadTexture("PSpeed", POTION_SPEED_PATH);
    _data->assets.loadTexture("PDamage", POTION_DAMAGE_PATH);
    _data->assets.loadTexture("SuperPotion", POTION_SUPER_POTION_PATH);

    _map = new Map(_data);
    _player = new Player(_data);
    _flash = new Flash(_data);

    // Spawners
    _spawners.push_back(Spawner(_data, sf::Vector2i(9, 4)));
    _spawners.push_back(Spawner(_data, sf::Vector2i(21, 7)));
    _spawners.push_back(Spawner(_data, sf::Vector2i(11, 11)));
    _spawners.push_back(Spawner(_data, sf::Vector2i(22, 14)));
    _spawners.push_back(Spawner(_data, sf::Vector2i(15, 18)));
    _spawners.push_back(Spawner(_data, sf::Vector2i(4, 19)));

    // Potions
    for(int i = 0; i < 8; i++){
        sf::Vector2f pos = randMapTile(_map->getMap()).sprite.getPosition();
        _potions.push_back(Potions(_data, randNumberBetween(3), pos));
    }
    // Super Potion
    _potions.push_back(Potions(_data, 3, sf::Vector2f(28 * TILE_SIZE * TILE_SCALE, 13 * TILE_SIZE * TILE_SCALE + TILE_SIZE * TILE_SCALE / 2)));
    _potions.push_back(Potions(_data, 3, sf::Vector2f(16 * TILE_SIZE * TILE_SCALE, 3 * TILE_SIZE * TILE_SCALE + TILE_SIZE * TILE_SCALE / 2)));

    // Variables
    _mouseDown = false;
    _gameState = GameStates::ePlaying;
    _firedProys = 0;

    // Win
    _winText.setFont(_data->assets.getFont("Monocraft"));
    _winText.setString("0");
    _winText.setCharacterSize(32);
    _winText.setFillColor(sf::Color::Red);
    _winText.setPosition(
        _data->window.getView().getCenter().x - _winText.getGlobalBounds().width / 2,
        _data->window.getView().getCenter().y - _winText.getGlobalBounds().height / 2
    );
}

void GameState::initView(){
    _view = _data->window.getView();
    _view.setCenter(_player->getSprite().getPosition());
    _view.setSize(static_cast<float>(_data->window.getSize().x), static_cast<float>(_data->window.getSize().y));
    _data->window.setView(_view);
}

void GameState::initHUD(){
    _playerHealthBarBox = sf::RectangleShape(sf::Vector2f(HUD_HEALTH_LENGTH, HUD_HEALTH_HEIGHT));
    _playerHealthBarBox.setFillColor(sf::Color::Black);
    _playerHealthBarBox.setOutlineColor(sf::Color::Black);
    _playerHealthBarBox.setOutlineThickness(2.f);
    _playerHealthBarBox.setPosition(15.0f, 15.0f);

    _playerHealthBarFill = sf::RectangleShape(sf::Vector2f(HUD_HEALTH_LENGTH, HUD_HEALTH_HEIGHT));
    _playerHealthBarFill.setFillColor(sf::Color::Green);
    _playerHealthBarFill.setPosition(15.0f, 15.0f);

    _hudText.setFont(_data->assets.getFont("Monocraft"));
    _hudText.setString("0");
    _hudText.setCharacterSize(16);
    _hudText.setFillColor(sf::Color::White);
    _hudText.setPosition(5, 50);

    _speedTimeBar = sf::RectangleShape(sf::Vector2f(HUD_POTION_LENGTH, HUD_POTION_HEIGTH));
    _damageTimeBar = sf::RectangleShape(sf::Vector2f(HUD_POTION_LENGTH, HUD_POTION_HEIGTH));
    _superPotionTimeBar = sf::RectangleShape(sf::Vector2f(HUD_POTION_LENGTH, HUD_POTION_HEIGTH));

    _speedTimeBar.setPosition(
        5, _hudText.getGlobalBounds().top + _hudText.getGlobalBounds().height + 5
    );

    _damageTimeBar.setPosition(
        5, _speedTimeBar.getGlobalBounds().top + _speedTimeBar.getGlobalBounds().height + 5
    );

    _superPotionTimeBar.setPosition(
        5, _damageTimeBar.getGlobalBounds().top + _damageTimeBar.getGlobalBounds().height + 5
    );

    _speedTimeBar.setFillColor(sf::Color::Cyan);
    _damageTimeBar.setFillColor(sf::Color::Magenta);
    _superPotionTimeBar.setFillColor(COLOR_YELLOW);
}
GameState::GameState(GameDataRef data) : _data(data){
    init();
    initView();
    initHUD();
}

GameState::~GameState(){
    delete _map;
    delete _player;
    delete _flash;
    delete _pauseScreen;
}

void GameState::handleInput()
{
    sf::Event ev;
    while(_data->window.pollEvent(ev)){
        if(sf::Event::Closed == ev.type) _data->window.close();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            if(!_keyDown){
                _keyDown = true;
                handlePause();
                if(getPaused()){
                    _pauseScreen = new PauseScreen(_data);
                }else{
                    delete _pauseScreen;
                }
            }
        }else _keyDown = false;

        if(!getPaused()){
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                if(!_mouseDown){
                    _mouseDown = true;
                    if(_player->getReloading() == false && _player->handleShoot()){
                        _firedProys++;
                        sf::Vector2i mousePosWindow = sf::Mouse::getPosition(_data->window);
                        sf::Vector2f mousePosView = _data->window.mapPixelToCoords(mousePosWindow, _view);
                        _proys.push_back(Proyectile(_data, _player->getDamage(), _player->getSprite(), mousePosView, _player->getMoving(), _player->getHasDamageEffect()));
                    }
                }
            }else{
                _mouseDown = false;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) _player->setReloading(true);


        }else{
            if(_data->input.isSpriteClicked(_pauseScreen->getSaveButton(), sf::Mouse::Left, _data->window)){
                if(!_mouseDown){
                    std::cout << "SAVE" << std::endl;
                    _mouseDown = true;
                }
            }else{
                _mouseDown = false;
            }

            if(_data->input.isSpriteClicked(_pauseScreen->getExitButton(), sf::Mouse::Left, _data->window)){
                if(!_mouseDown){
                    _mouseDown = true;
                    exit(-1);
                }
            }else{
                _mouseDown = false;
            }
        }
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
                _spawners.erase(_spawners.begin() + s);
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
            enemy.animate();
            checkHit(i, e);
            if(enemy.getSprite().getGlobalBounds().intersects(_player->getSprite().getGlobalBounds()) && enemy.getAttackClock().getElapsedTime().asSeconds() > ENEMY_ATTACK_SPEED){
                if(!_player->takeDamage(enemy.getDamage())) endGame();
                updateHUD();
                enemy.getAttackClock().restart();
            }
        }
    }
}

void GameState::updatePlayer(float dt){
    for(unsigned int i = 0; i < _potions.size(); i++){
        if(spriteCollision(_player->getSprite(), _potions[i].getSprite())){
            _player->pickPotion(_potions[i]);
            _potions.erase(_potions.begin() + i);
        }
    }
    _player->update(dt);
}


void GameState::handleCollision(){
    std::vector<MapTile> _walls = _map->getWalls();
    std::vector<MapTile> _details = _map->getDetails();
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

    for(int i = 0; i < _details.size(); i++){
        sf::FloatRect detailBounds = _details[i].sprite.getGlobalBounds();


        _player->handleCollision(detailBounds);

        for(unsigned int i = 0; i < _proys.size(); i++){
            if(detailBounds.intersects(_proys[i].getSprite().getGlobalBounds())) _proys.erase(_proys.begin() + i);
        }
        for(unsigned int i = 0; i < _spawners.size(); i++){
            _spawners[i].handleEnemyCollision(detailBounds);
        }
    }
}

void GameState::handleWin(){
    if(spriteCollision(_player->getSprite(), _map->getWinArea()) && !_spawners.size()){
        winGame();
    }
}

void GameState::updateHUD(){
    float percent = _player->getHealth() / _player->getMaxHealth();
    _playerHealthBarFill.setSize(sf::Vector2f(HUD_HEALTH_LENGTH * percent, HUD_HEALTH_HEIGHT));
    _playerHealthBarFill.setFillColor(generateHealthColor(percent));

    std::stringstream ss;
    if(_player->getReloading()){
        ss << "Reloading...";
    }else{
        ss << "Ammo: " << _player->getAmmo() << "/" << _player->getMaxAmmo();
    }

    !_player->getAmmo() || _player->getReloading() ? _hudText.setColor(sf::Color::Red) : _hudText.setColor(sf::Color::White);
    _hudText.setString(ss.str());

    if(_player->getHasSpeedEffect()){
        float percent = 1 - (_player->getSpeedEffectClock().getElapsedTime().asSeconds() / POTION_DURATION);
        _speedTimeBar.setSize(sf::Vector2f(HUD_POTION_LENGTH * percent , HUD_POTION_HEIGTH));
    }

    if(_player->getHasDamageEffect()){
        float percent = 1 - (_player->getDamageEffectClock().getElapsedTime().asSeconds() / POTION_DURATION);
        _damageTimeBar.setSize(sf::Vector2f(HUD_POTION_LENGTH * percent , HUD_POTION_HEIGTH));
    }

    if(_player->getHasSuperPotionEffect()){
        float percent = 1 - (_player->getSuperPotionEffectClock().getElapsedTime().asSeconds() / POTION_DURATION);
        _superPotionTimeBar.setSize(sf::Vector2f(HUD_POTION_LENGTH * percent , HUD_POTION_HEIGTH));
    }
}

void GameState::update(float dt){
    sf::Time elapsed = _gameClock.restart();
    if(!getPaused()){
        if(_gameState == GameStates::ePlaying){
            _gameTime += elapsed;
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
            updateHUD();
            handleWin();
            _view.setCenter(_player->getSprite().getPosition());
            _data->window.setView(_view);
        }

        if(_gameState == GameStates::eGameOver){
            for(unsigned int i = 0; i < _spawners.size(); i++){
                _spawners[i].despawnAll();
            }
            _flash->show(dt);
            if(_endGameClock.getElapsedTime().asSeconds() > TIME_BEFORE_GAME_OVER){
                _data->machine.addState(StateRef( new GameOverState(_data)));
            }
        }

        if(_gameState == GameStates::eWin){
            _flash->show(dt);
            if(_endGameClock.getElapsedTime().asSeconds() > TIME_BEFORE_GAME_OVER){
                _data->machine.addState(StateRef( new WinState(_data, calculateScore( _gameTime.asSeconds(), _firedProys ) )));
            }
        }
    }else{
        _pauseScreen->update();
    }
}

void GameState::drawHUD(){
    _data->window.draw(_playerHealthBarBox);
    _data->window.draw(_playerHealthBarFill);
    _data->window.draw(_hudText);

    if(_player->getHasSpeedEffect()){
        _data->window.draw(_speedTimeBar);
    }

    if(_player->getHasDamageEffect()){
        _data->window.draw(_damageTimeBar);
    }

    if(_player->getHasSuperPotionEffect()){
        _data->window.draw(_superPotionTimeBar);
    }
}

void GameState::draw(float dt){

    if(!getPaused()){
        _data->window.clear(COLOR_BG_BLUE);
        _data->window.setView(_view);

        _map->drawLightEffect();
        _map->draw();
        _map->drawFilter();
        if(!_spawners.size()){
            _map->drawWinSprite();
        }

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



        if(_spawners.size() != 0 && spriteCollision(_player->getSprite(), _map->getWinArea())){
            _winText.setString("Destroy all spawners to escape!");
            _winText.setPosition(
                _data->window.getView().getCenter().x - _winText.getGlobalBounds().width / 2,
                _data->window.getView().getCenter().y - _winText.getGlobalBounds().height / 2
            );
            _data->window.draw(_winText);
        }

        _data->window.setView(_data->window.getDefaultView());
        drawHUD();
        _flash->draw();
    }else{
        _pauseScreen->draw();
    }
        _data->window.display();

}

void GameState::endGame(){
    _gameState = GameStates::eGameOver;
    _endGameClock.restart();
}

void GameState::winGame(){
    _gameState = GameStates::eWin;
    _endGameClock.restart();
}
