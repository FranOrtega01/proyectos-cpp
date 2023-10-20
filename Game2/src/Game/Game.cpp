#include "Game.h"

void Game::initWindow(){
    this->videoMode = sf::VideoMode(800, 600);
    this->window = new sf::RenderWindow(this->videoMode, "Ramon Games - Game 2", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
    spawnTimerMax = 10.f;
    spawnTimer = spawnTimerMax;
    maxBalls = 10;
}

void Game::initVars(){
    this->endGame = false;
}

void Game::initFont(){
    if(!font.loadFromFile("Fonts/Monocraft.otf")){
        cout << "Error initializing font" << endl;
    }
    
}

void Game::initText(){
    guiText.setFont(font);
    guiText.setFillColor(sf::Color::White);
    guiText.setCharacterSize(18);

    endGameText.setFont(font);
    endGameText.setFillColor(sf::Color::Red);
    endGameText.setCharacterSize(60);
    endGameText.setString("GAME OVER");
    endGameText.setPosition((window->getSize().x - endGameText.getGlobalBounds().width) / 2, (window->getSize().y  - endGameText.getGlobalBounds().height) / 2);
}

// Constructor & Destructor
Game::Game(){
    this->initVars();
    this->initWindow();
    this->initFont();
    this->initText();
}

Game::~Game(){
    delete this->window;
}

// Functions
const bool Game::running() const{
    return this->window->isOpen();

}

const bool &Game::getEndGame() const{
    return endGame;
}

void Game::pollEvents(){
    while(this->window->pollEvent(this->ev)){
        switch(this->ev.type){
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if(this->ev.key.code == sf::Keyboard::Escape) this->window->close();
                break;
        }
    }
}

const int Game::randomizeType(){
    int type = ballTypes::DEFAULT;

    int randValue = rand() % 100 + 1;

    if(randValue > 60 && randValue <= 80) type = ballTypes::DAMAGING;
    else if(randValue > 80) type = ballTypes::HEALING;



    return type;
}

void Game::spawnBalls(){
    if(spawnTimer < spawnTimerMax){
        spawnTimer += 1.f;
    }else{
        if(balls.size() < maxBalls){
            balls.push_back(Ball(*window, randomizeType()));
            spawnTimer = 0.f;
        }
    }
}

void Game::updatePlayer(){
    player.update(window);
    if(player.getHp() <= 0) endGame = true;
}

void Game::updateCollision(){
    for (size_t i = 0; i < balls.size(); i++){
        if(player.getShape().getGlobalBounds().intersects(balls[i].getShape().getGlobalBounds())){

            switch (balls[i].getType())
            {
            case ballTypes::DEFAULT:
                player.setPoints(player.getPoints() + 1);
                break;
            case ballTypes::DAMAGING:
                player.takeDamage(10);
                break;
            case ballTypes::HEALING:
                player.gainHealth(1);
                break;
            default:
                break;
            }

            balls.erase(balls.begin() + i);
        }
    }   
}

void Game::updateGUI(){
    stringstream ss;
    ss << "Points: " << player.getPoints() << "\n" << "Health: " << player.getHp() << "/" << player.getHpMax();
    guiText.setString(ss.str());
}

void Game::update(){
    pollEvents();
    if(!endGame){
        spawnBalls();
        updatePlayer();
        updateCollision();
        updateGUI();
    }
}

void Game::renderGUI(sf::RenderTarget* target){
    target->draw(guiText);
}

void Game::draw(){
    player.render(window);
    for(auto i: balls){
        i.render(*window);
    }
    renderGUI(window);
}

void Game::render(){
    window->clear();
    draw();
    if(endGame){
        window->clear();
        window->draw(endGameText);
    }
    window->display();
}

void Game::run(){
    update();
    render();
}
