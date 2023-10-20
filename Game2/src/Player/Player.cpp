#include "Player.h"

void Player::initVars(){
    hpMax = 10;
    hp = hpMax;
    points = 0;
    movementSpeed = 5.f;
}

void Player::initShape(){
    shape.setFillColor(sf::Color::Green);
    shape.setSize(sf::Vector2f(50.f, 50.f));
}

// Constructor & Destructor
Player::Player(float x, float y){
    shape.setPosition(x,y);
    initVars();
    initShape();
}

Player::~Player(){

}

// Getters
const sf::RectangleShape &Player::getShape() const{
    return shape;
}

const int &Player::getHp() const{
    return hp;
}

const int &Player::getHpMax() const{
    return hpMax;
}

int Player::getPoints(){return points;}

// Setters
void Player::setPoints(int points){
    this->points = points;
}


// Functions
void Player::takeDamage(const int damage){
    hp = hp - damage < 0 ? 0 : hp - damage;
}

void Player::gainHealth(const int health){
    hp = hp + health > hpMax ? hpMax : hp + health;
}

void Player::updateInput(){
    int updatedSpeed = movementSpeed + points*0.5 ;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        this->shape.move(-updatedSpeed, 0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        this->shape.move(updatedSpeed, 0.f);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        this->shape.move(0.f,-updatedSpeed);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        this->shape.move(0.f, updatedSpeed);
    }
}

void Player::updateWindowBoundsCollision(sf::RenderTarget* target){

    // Left & Right
    if(this->shape.getGlobalBounds().left < 0.f){
        this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);
    }else if(this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width > target->getSize().x){
        this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);
    }

    // Top & Bottom
    if(this->shape.getGlobalBounds().top <= 0.f){
        this->shape.setPosition(this->shape.getGlobalBounds().left, 0.f);
    }else if(this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y){
        this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height);
    }
}

void Player::update(sf::RenderTarget* target){
    this->updateInput();
    this->updateWindowBoundsCollision(target);
}

void Player::draw(){

}

void Player::render(sf::RenderTarget* target){
    target->draw(this->shape);
}