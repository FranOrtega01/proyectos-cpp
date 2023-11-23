#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <cmath>

float distance(sf::Vector2f a, sf::Vector2f b);

sf::Vector2f randomCoord(sf::Vector2f center, float r);

sf::Color generateHealthColor(float percent);

bool spriteCollision(sf::Sprite s1, sf::Sprite s2);
bool spriteCollision(sf::Sprite s1, sf::RectangleShape s2);

int randNumberBetween(int number);

MapTile randMapTile(std::vector<MapTile> tiles);


#endif // FUNCTIONS_H
