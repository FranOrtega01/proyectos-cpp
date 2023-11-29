#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "DEFINITIONS.h"
#include <cmath>

void stringToChar(char *charRef, sf::Text str);

void stringToChar(char *charRef, sf::String str);

// Vectors
float distance(sf::Vector2f a, sf::Vector2f b);
sf::Vector2f randomCoord(sf::Vector2f center, float r);

int randNumberBetween(int number);
// GUI Color
sf::Color generateHealthColor(float percent);
// Collisions
bool spriteCollision(sf::Sprite s1, sf::Sprite s2);
bool spriteCollision(sf::Sprite s1, sf::RectangleShape s2);
bool spriteBoundsBottomCollision(sf::FloatRect b1, sf::FloatRect b2);
bool spriteBoundsTopCollision(sf::FloatRect b1, sf::FloatRect b2);
bool spriteBoundsRightCollision(sf::FloatRect b1, sf::FloatRect b2);
bool spriteBoundsLeftCollision(sf::FloatRect b1, sf::FloatRect b2);


// Mouse 
bool isMouseInside(sf::Sprite sprite, sf::RenderWindow& window);
bool isMouseInside(sf::RectangleShape sprite, sf::RenderWindow& window);

// Map Tiles
MapTile randMapTile(std::vector<MapTile> tiles);
std::vector<MapTile> getAdjacentTiles(sf::Sprite sprite, std::vector<MapTile> tiles);

// Score
int calculateScore(float time, int proys);


#endif // FUNCTIONS_H
