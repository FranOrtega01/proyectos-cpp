#include "Game.h"

int generateRandomType() {
    int randomValue = rand() % 100;

    if (randomValue < 10) {
        return 0; 
    } else if (randomValue < 25) {
        return 1; 
    } else if (randomValue < 40) {
        return 2; 
    } else if (randomValue < 70) {
        return 3; 
    } else {
        return 4; 
    }
}

// Private Functions
void Game::initVariables(){
    this->window = nullptr;

    // Game Logic
    this->points = 0;
    this->enemySpawnTimerMax = 20.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 10;
    this->mouseDown = false;
    this->health = 10;
    this->endGame = false;
}

void Game::initFonts(){
    this->font.loadFromFile("Fonts/Monocraft.otf");
}

void Game::initTexts(){
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(16);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NONE");
}

void Game::initWindow(){
    this->videoMode.height = 600;
    this->videoMode.width = 800;

    this->window = new sf::RenderWindow(this->videoMode, "Ramon Games", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);
}

void Game::initEnemies(){
    this->enemy.setPosition(0.f, 0.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    // this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Cyan);
}

// Constructor & Destructor
Game::Game(){
    this->initVariables();
    this->initFonts();
    this->initTexts();
    this->initWindow();
    this->initEnemies();
}

Game::~Game(){
    delete this->window;
}

// Accessors

const bool Game::running() const{
    return this->window->isOpen();
}

const bool Game::getEndGame() const{
    return this->endGame;
}

// Game Functions

void Game::spawnEnemy(){
    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        0.f
    );

    // Random enemy type
    int type = generateRandomType();

    switch(type){
        case 0:
            this->enemy.setFillColor(sf::Color::Magenta);
            this->enemy.setSize(sf::Vector2f(20.f, 20.f));
            break;
        case 1:
            this->enemy.setFillColor(sf::Color::Blue);
            this->enemy.setSize(sf::Vector2f(35.f, 35.f));
            break;
        case 2:
            this->enemy.setFillColor(sf::Color::Cyan);
            this->enemy.setSize(sf::Vector2f(50.f, 50.f));
            break;
        case 3:
            this->enemy.setFillColor(sf::Color::Red);
            this->enemy.setSize(sf::Vector2f(70.f, 70.f));
            break;
        case 4:
            this->enemy.setFillColor(sf::Color::Green);
            this->enemy.setSize(sf::Vector2f(100.f, 100.f));
            break;
        default:
            this->enemy.setFillColor(sf::Color::Yellow);
            this->enemy.setSize(sf::Vector2f(100.f, 100.f));
            break;
    }
    this->enemies.push_back(this->enemy);
}

// Game Functions
void Game::pollEvents(){
    while(this->window->pollEvent(this->e)){
        switch(this->e.type){
            case sf::Event::Closed:
                this->window->close(); 
                break;
            case sf::Event::KeyPressed:
                if(this->e.key.code == sf::Keyboard::Escape){
                    this->window->close();
                }
                break;
        }
    }
}

void Game::updateMousePos(){
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies(){
    if(this->enemies.size() < this->maxEnemies){
        if(this->enemySpawnTimer >= this->enemySpawnTimerMax){
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }else{
            this->enemySpawnTimer += 1.f;
        }
    }

    // Move & Update enemies
    for(int i = 0; i < this->enemies.size(); i++){
        this->enemies[i].move(0.f, 3.f);

        // Enemy out of window
        if(this->enemies[i].getPosition().y > this->window->getSize().y){
            if(this->enemies[i].getFillColor() == sf::Color::Magenta){
                this->health -= 3;
            }else{
                this->health--;
            }
            this->enemies.erase(this->enemies.begin() + i);
        }
    }   

    // Check if clicked
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if(!this->mouseDown){
            this->mouseDown = true;

            for(size_t i = 0; i < this->enemies.size(); i++){
                if(this->enemies[i].getGlobalBounds().contains(this->mousePosView)){
                    // Gain points
                    if(this->enemies[i].getFillColor() == sf::Color::Magenta){this->points += 10;}
                    else if(this->enemies[i].getFillColor() == sf::Color::Blue){this->points += 7;}
                    else if(this->enemies[i].getFillColor() == sf::Color::Cyan){this->points += 5;}
                    else if(this->enemies[i].getFillColor() == sf::Color::Red){this->points += 3;}
                    else{this->points += 1;}
                    // Delete enemy
                    this->enemies.erase(this->enemies.begin() + i);
                    break;
                }
            }
        }
    }else{
        this->mouseDown = false;
    } 
}

void Game::updateText(){
    stringstream ss;
    ss << "Points: " << this->points << "\n" << "Health: " << this->health;
    this->uiText.setString(ss.str());
}

void Game::update(){
    this->pollEvents();
    if(!this->endGame){
        this->updateMousePos();
        this->updateText();
        this->updateEnemies();
    }
    if(this->health <= 0) this->endGame = true;
}   

void Game::renderText(sf::RenderTarget& target){
    target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget& target){
    for(auto &e : this->enemies){
        target.draw(e);
    }  
}

void Game::render(){
    this->window->clear();

    // Draw game objects
    this->renderEnemies(*this->window);
    this->renderText(*this->window);
    this->window->display();
}

