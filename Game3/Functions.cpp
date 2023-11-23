#include "Functions.h"

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

int randNumberBetween(int number){
    return rand()%number;
}
MapTile randMapTile(std::vector<MapTile> tiles){
    return tiles[rand() % tiles.size()];
}
