#include "Ball.h"

// Init
void Ball::initShape(const sf::RenderWindow& window){
    shape.setRadius(static_cast<float>(rand()%10+10));

    sf::Color color;

    switch(type){
        case DEFAULT:
            color = sf::Color::White;
            break;
        case DAMAGING:
            color = sf::Color::Red;
            break;
        case HEALING:
            color = sf::Color::Green;
            break;
    }
    shape.setFillColor(color);
    float shapePosX = static_cast<float>(rand() % window.getSize().x - this->shape.getGlobalBounds().width);
    float shapePosY = static_cast<float>(rand() % window.getSize().y - this->shape.getGlobalBounds().height);

    if (shapePosX < 0.f) {
        shapePosX = 0.f;
    }

    if(shapePosY < 0.f){
        shapePosY = 0.f;
    }

    this->shape.setPosition(sf::Vector2f(shapePosX, shapePosY));

}

// Constructors & Destructors
Ball::Ball(const sf::RenderWindow& window, int type) : type(type){
    this->type = type;
    initShape(window);
}

Ball::~Ball(){

}

// Getters
const sf::CircleShape &Ball::getShape() const{
    return shape;
}

const int &Ball::getType() const{
    return type;
}

// Functions
void Ball::update(){

}

void Ball::render(sf::RenderTarget &target){
    target.draw(shape);
}
