#include "Functions.h"
#include <iostream>

void stringToChar(char *charRef, sf::Text text){
    sf::String str = text.getString();
    for (std::size_t i = 0; i < str.getSize(); ++i) {
        charRef[i] = static_cast<char>(str[i]);
        }

        charRef[str.getSize()] = '\0';
}

void stringToChar(char *charRef, sf::String str){
    for (std::size_t i = 0; i < str.getSize(); ++i) {
    charRef[i] = static_cast<char>(str[i]);
    }

    charRef[str.getSize()] = '\0';
}

float distance(sf::Vector2f a, sf::Vector2f b){
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

sf::Vector2f randomCoord(sf::Vector2f center, float r){
    float randAng = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2 * M_PI;
    return sf::Vector2f(center.x + r * cos(randAng), center.y + r * sin(randAng));
}

sf::Color generateHealthColor(float percent){
    int green = 255 * percent;
    return sf::Color(255 - green, green,0);
}

bool spriteCollision(sf::Sprite s1, sf::Sprite s2){
    return s1.getGlobalBounds().left < s2.getGlobalBounds().left + s2.getGlobalBounds().width 
        && s1.getGlobalBounds().left + s1.getGlobalBounds().width > s2.getGlobalBounds().left
        && s1.getGlobalBounds().top < s2.getGlobalBounds().top + s2.getGlobalBounds().height 
        && s1.getGlobalBounds().top + s1.getGlobalBounds().height > s2.getGlobalBounds().top
    ;
}

bool spriteCollision(sf::Sprite s1, sf::RectangleShape s2){
    return s1.getGlobalBounds().left < s2.getGlobalBounds().left + s2.getGlobalBounds().width 
        && s1.getGlobalBounds().left + s1.getGlobalBounds().width > s2.getGlobalBounds().left
        && s1.getGlobalBounds().top < s2.getGlobalBounds().top + s2.getGlobalBounds().height 
        && s1.getGlobalBounds().top + s1.getGlobalBounds().height > s2.getGlobalBounds().top
    ;
}

bool spriteBoundsBottomCollision(sf::FloatRect b1, sf::FloatRect b2){
    return b1.top < b2.top &&
            b1.top + b1.height < b2.top + b2.height &&
            b1.left < b2.left + b2.width &&
            b1.left + b1.width > b2.left;
}
bool spriteBoundsTopCollision(sf::FloatRect b1, sf::FloatRect b2){
    return b1.top > b2.top &&
        b1.top + b1.height > b2.top + b2.height &&
        b1.left < b2.left + b2.width &&
        b1.left + b1.width > b2.left;
}
bool spriteBoundsRightCollision(sf::FloatRect b1, sf::FloatRect b2){
    return b1.left < b2.left &&
        b1.left + b1.width < b2.left + b2.width &&
        b1.top < b2.top + b2.height &&
        b1.top + b1.height > b2.top;
}

bool spriteBoundsLeftCollision(sf::FloatRect b1, sf::FloatRect b2){
    return b1.left > b2.left &&
        b1.left + b1.width > b2.left + b2.width &&
        b1.top < b2.top + b2.height &&
        b1.top + b1.height > b2.top;
}

bool isMouseInside(sf::Sprite sprite, sf::RenderWindow& window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f mousePositionInView = window.mapPixelToCoords(mousePosition);

    return sprite.getGlobalBounds().contains(mousePositionInView);
}

bool isMouseInside(sf::RectangleShape sprite, sf::RenderWindow& window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f mousePositionInView = window.mapPixelToCoords(mousePosition);

    return sprite.getGlobalBounds().contains(mousePositionInView);
}

int randNumberBetween(int number){
    return rand()%number;
}
MapTile randMapTile(std::vector<MapTile> tiles){
    return tiles[rand() % tiles.size()];
}

int calculateScore(float time, int proys){
    float timeScore = HIGHSCORE_K / time;
    float proysScore = HIGHSCORE_K / (proys + 1);
    float weightedScore = HIGHSCORE_W * timeScore + (1 - HIGHSCORE_W) * proysScore;
    return static_cast<int>(weightedScore * 1000);
}
